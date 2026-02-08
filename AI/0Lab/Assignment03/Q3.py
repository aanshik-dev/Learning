import pandas as pd
import numpy as np
from PIL import Image

img = Image.open('Learning\AI\Assignment03\cat.jpg').convert('L')
img_array = np.array(img)

df_original = pd.DataFrame(img_array)
df_original.to_csv('image_data.csv', index=False)
print("Image saved to image_data.csv successfully.")

df_imported = pd.read_csv('image_data.csv')

df_sliced = df_imported.iloc[:-1, :-1]

print("\nOriginal Shape:", df_imported.shape)
print("Sliced Shape (excluding last row/col):", df_sliced.shape)
print("\nFirst few rows of the sliced matrix:")
print(df_sliced.head())