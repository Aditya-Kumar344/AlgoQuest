# Deep Compression of a Multimodal Fruit Classification Network

Implementation of the Deep Compression pipeline (Han et al., ICLR 2016) applied
to a custom multimodal neural network for 257-class fruit classification on the
Fruits-360 dataset. The model fuses LBP texture maps, Canny edge maps, and 12
handcrafted color/shape features — compressed via pruning, quantization, and
Huffman coding from scratch.

---

## Project Structure

```
CNN_Project/
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
    └── huffman.npz
```

---

## How to Run

### 1. Install dependencies

```bash
pip install torch torchvision opencv-python numpy scikit-learn \
            kagglehub tqdm psutil
```

### 2. Set up Kaggle credentials (for dataset download)

```bash
# Place your kaggle.json in ~/.kaggle/
mkdir -p ~/.kaggle
cp kaggle.json ~/.kaggle/
chmod 600 ~/.kaggle/kaggle.json
```

### 3. Run the full pipeline

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

### 4. Running on Google Colab

```python
# At the top of your Colab notebook
!pip install kagglehub tqdm psutil opencv-python scikit-learn -q

# Upload kaggle.json then run
import os
os.makedirs('/root/.kaggle', exist_ok=True)
!cp kaggle.json /root/.kaggle/
!chmod 600 /root/.kaggle/kaggle.json

!python main.py
```

---

## Downloading Pre-trained Models

All four compressed models are available on Google Drive:

| Model | Description | Size | Link |
|---|---|---|---|
| `baseline.npz` | Fully trained, no compression | 49.37 MB | [Download](#) |
| `pruned.npz` | 99.6% weights pruned + retrained | 5.22 MB | [Download](#) |
| `quantized.npz` | k=16 quantization + retrained | 5.22 MB | [Download](#) |
| `huffman.npz` | Huffman coded final model | 0.35 MB | [Download](#) |

> **Note:** Replace `[Download](#)` links above with your actual Google Drive
> sharing links after uploading the files.

### How to upload to Google Drive (from Colab)

```python
from google.colab import drive
drive.mount('/content/drive')

import shutil
shutil.copy('compressed_models/baseline.npz',
            '/content/drive/MyDrive/CNN_Project/baseline.npz')
shutil.copy('compressed_models/pruned.npz',
            '/content/drive/MyDrive/CNN_Project/pruned.npz')
shutil.copy('compressed_models/quantized.npz',
            '/content/drive/MyDrive/CNN_Project/quantized.npz')
shutil.copy('compressed_models/huffman.npz',
            '/content/drive/MyDrive/CNN_Project/huffman.npz')
print("All models uploaded.")
```

---

## Loading a Pre-trained Model

```python
import torch
from models import cifar_model
from utils  import load_model_from_npz

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Load any checkpoint — all are interchangeable
model = cifar_model(num_classes=257).to(device)
model = load_model_from_npz(model, "compressed_models/quantized.npz", device)

model.eval()
```

### Loading from Google Drive (Colab)

```python
import gdown

# Replace FILE_ID with the ID from your Google Drive share link
# Share link format: https://drive.google.com/file/d/FILE_ID/view
gdown.download(
    "https://drive.google.com/uc?id=YOUR_FILE_ID",
    "compressed_models/quantized.npz",
    quiet=False
)

model = cifar_model(num_classes=257).to(device)
model = load_model_from_npz(model, "compressed_models/quantized.npz", device)
```

### Running inference

```python
from data import data_loader
import os

# Point to your local dataset
training = "path/to/fruits-360/Training"
test_dir = "path/to/fruits-360/Test"

_, test_loader = data_loader(training, test_dir)

# Run evaluation
from utils import test_eval
accuracy = test_eval(model, test_loader, device)
print(f"Accuracy: {accuracy:.2f}%")
```

---

## Results

The full pipeline compresses a 49.37 MB model to 0.35 MB with negligible
accuracy loss:

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
  Final Compression Ratio               139.3x      ≥9x

  3. RUNTIME MEMORY
  GPU VRAM Used                         546.8 MB
  RAM Used by Process                  1824.7 MB
  Total Parameters                    19,784,385
  Weights Pruned             19,708,673 / 19,781,920   (99.6% sparse)

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
