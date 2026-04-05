# Deep Compression of a Multimodal Fruit Classification Network

Implementation of the Deep Compression pipeline (Han et al., ICLR 2016) applied
to a custom multimodal neural network for 257-class fruit classification on the
Fruits-360 dataset. The model fuses LBP texture maps, Canny edge maps, and 12
handcrafted color/shape features — compressed via pruning, quantization, and
Huffman coding implemented from scratch.

---

## Project Structure

```
Final_Project/
│
├── main.py                        # Entry point — runs full pipeline
├── config.py                      # Device selection (CUDA / MPS / CPU)
│
├── data/
│   ├── __init__.py
│   └── data_loader.py             # Dataset class, LBP, Canny, feature extraction
│
├── models/
│   ├── __init__.py
│   └── model_cifar.py             # SmallCIFARNet architecture
│
├── compression/
│   ├── __init__.py
│   ├── conv2d.py                  # modified_conv2d (prune + quantize aware)
│   ├── linear.py                  # modified_linear (prune + quantize aware)
│   ├── prune.py                   # prune_model(), count_sparsity()
│   ├── quantization.py            # quantize_model()
│   └── huffman.py                 # Huffman coding from scratch
│
├── utils/
│   ├── __init__.py
│   ├── training.py                # train_model(), evaluate(), train_and_eval()
│   ├── test_eval.py               # test_eval(), print_compression_table()
│   └── loading.py                 # save_model_npz(), load_model_from_npz()
│
└── compressed_models/             # Auto-created, stores all .npz checkpoints
    ├── baseline.npz
    ├── pruned.npz
    ├── quantized.npz
    └── compressed.npz

```

---

## How to Run

### 1. Install dependencies

```bash
pip install torch torchvision opencv-python numpy scikit-learn \
            kagglehub tqdm psutil
```

### 2. Run the full pipeline

```bash
python main.py
```

This will automatically:
- Download the Fruits-360 dataset via `kagglehub`
- Train the baseline model (10 epochs)
- Apply pruning + retrain (5 epochs)
- Apply quantization + retrain (5 epochs)
- Apply Huffman coding
- Save all 4 models to `compressed_models/`
- Print the full compression results table

### 3. Running on Google Colab

```python
!pip install kagglehub tqdm psutil opencv-python scikit-learn -q
!python main.py
```

---

## Pre-trained Models

All four compressed models are available on Google Drive.
Download whichever checkpoint you need:

| Model | Description | Size | Link |
|---|---|---|---|
| `baseline.npz` | Fully trained, no compression | 49.37 MB | [Download](https://drive.google.com/file/d/1Lb2fTr3Es_Wk86aL6rO-9fZ91hjpvoJD/view?usp=sharing) |
| `pruned.npz` | 99.6% weights pruned + retrained | 5.22 MB | [Download](https://drive.google.com/file/d/1mUrhgQFpseZNszXVfT2P3HO82wkSPD29/view?usp=sharing) |
| `quantized.npz` | k=16 quantization + retrained | 5.22 MB | [Download](https://drive.google.com/file/d/11lSP5Wv9WbJT44zdtFII3PJ3zATAzm3u/view?usp=sharing) |
| `compressed.npz` | Huffman coded final model | 0.35 MB | [Download](https://drive.google.com/file/d/1iV8nbE-Md2oUhKE0sU7liEzR3jeMJ4Km/view?usp=sharing) |


---

## Using a Downloaded Model

### Step 1 — Download the file

Click the Drive link above and save the `.npz` file, or download it directly:

```bash
pip install gdown
```

```python
import gdown

# Get FILE_ID from the Drive share link:
# https://drive.google.com/file/d/FILE_ID/view
gdown.download(
    "https://drive.google.com/uc?id=YOUR_FILE_ID",
    "compressed_models/quantized.npz",
    quiet=False
)
```

### Step 2 — Load the model

```python
import torch
from models import cifar_model
from utils  import load_model_from_npz

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

model = cifar_model(num_classes=257).to(device)
model = load_model_from_npz(model, "compressed_models/quantized.npz", device)
model.eval()
```

Any of the four `.npz` files can be loaded this way — same code, just change
the filename.

### Step 3 — Evaluate on the test set

```python
import os
import kagglehub
from data import data_loader
from utils import test_eval

path     = kagglehub.dataset_download("moltean/fruits")
path     = os.path.join(path, "fruits-360_100x100", "fruits-360")
training = os.path.join(path, "Training")
test_dir = os.path.join(path, "Test")

_, test_loader = data_loader(training, test_dir)
accuracy = test_eval(model, test_loader, device)
print(f"Accuracy: {accuracy:.2f}%")
```

### Step 4 — Run inference on a single image

```python
import cv2
import torch
from data.data_loader import (get_lbp, get_canny,
                               extract_color_features,
                               extract_shape_features)

def predict(image_path, model, device):
    img  = cv2.imread(image_path)
    img  = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img  = cv2.resize(img, (100, 100))
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

    batch = {
        "lbp": torch.tensor(get_lbp(gray)).unsqueeze(0).unsqueeze(0)
               .float().to(device) / 255.0,
        "canny": torch.tensor(get_canny(gray)).unsqueeze(0).unsqueeze(0)
                 .float().to(device) / 255.0,
        "color_features": torch.tensor(extract_color_features(img))
                          .unsqueeze(0).float().to(device),
        "shape_features": torch.tensor(extract_shape_features(gray))
                          .unsqueeze(0).float().to(device),
    }

    with torch.no_grad():
        pred_idx = model(batch).argmax(dim=1).item()

    return pred_idx

pred = predict("apple.jpg", model, device)
print(f"Predicted class index: {pred}")
```

---

## Results

```
------------------------------------------------------------
  DEEP COMPRESSION RESULTS
------------------------------------------------------------

  1. ACCURACY
  Baseline                              97.18%
  After Pruning  (before retrain)       61.70%   (loss 35.48%)
  After Pruning  (recovered)            96.98%   (Δ -0.20%)
  After Quantization (before retrain)   96.28%   (loss 0.70%)
  After Quantization (recovered)        97.10%   (Δ -0.08%)
  Total Accuracy Drop                   0.08%    within 1.5%

  2. STORAGE MEMORY
  Baseline (.npz)                       49.37 MB
  After Pruning (.npz)                   5.22 MB   (89.4% smaller   9.5x)
  After Quantization (.npz)              5.22 MB   (89.4% smaller   9.5x)
  Huffman Compressed (.npz)              0.35 MB   (99.3% smaller 139.3x)
  Final Compression Ratio                139.3x     ≥9x

  3. RUNTIME MEMORY
  GPU VRAM Used                         546.8 MB
  RAM Used by Process                  1824.7 MB
  Total Parameters                    19,784,385
  Weights Pruned         19,708,673 / 19,781,920   (99.6% sparse)

  4. COMPRESSION DETAILS
  Quantization                          k=16 centroids   (~4-bit)
  Bits/weight after pruning+quant       0.0148
  Bits/weight after Huffman             1.03             (target 3.57)
  Huffman coding gain                   15.51x over quantized

------------------------------------------------------------
```

| Metric | Target | Achieved |
|---|---|---|
| Compression ratio | ≥ 9× | **139×** |
| Accuracy drop | ≤ 1.5% | **0.08%** |
| Bits per weight | ≈ 3.57 | **1.03** |
| Baseline accuracy | — | **97.18%** |

---

## Reference

> Song Han, Huizi Mao, William J. Dally.
> *Deep Compression: Compressing Deep Neural Networks with Pruning,
> Trained Quantization and Huffman Coding.*
> ICLR 2016. [arXiv:1510.00149](https://arxiv.org/abs/1510.00149)
