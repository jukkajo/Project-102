import os
import shutil
import random

def split_dataset(dataset_path, train_ratio=0.8, test_ratio=0.1, valid_ratio=0.1, seed=None):
    # Set seed for reproducibility
    random.seed(seed)

    # Create destination folders
    train_folder = os.path.join(dataset_path, 'train')
    test_folder = os.path.join(dataset_path, 'test')
    valid_folder = os.path.join(dataset_path, 'valid')

    os.makedirs(train_folder, exist_ok=True)
    os.makedirs(test_folder, exist_ok=True)
    os.makedirs(valid_folder, exist_ok=True)

    # Get list of all files in the dataset folder
    files = os.listdir(dataset_path)

    # Filter out non-image and non-text files
    image_files = [file for file in files if file.lower().endswith(('.jpg', '.jpeg', '.png'))]
    text_files = [file for file in files if file.lower().endswith('.txt')]

    # Shuffle the files randomly
    random.shuffle(image_files)

    # Calculate the split indices
    train_split = int(train_ratio * len(image_files))
    test_split = int(test_ratio * len(image_files))

    # Divide the dataset into train, test, and valid sets
    train_images = image_files[:train_split]
    test_images = image_files[train_split:train_split + test_split]
    valid_images = image_files[train_split + test_split:]

    # Move images and corresponding text files to respective folders
    for image in train_images:
        shutil.move(os.path.join(dataset_path, image), os.path.join(train_folder, image))
        text_file = os.path.splitext(image)[0] + '.txt'
        if text_file in text_files:
            shutil.move(os.path.join(dataset_path, text_file), os.path.join(train_folder, text_file))

    for image in test_images:
        shutil.move(os.path.join(dataset_path, image), os.path.join(test_folder, image))
        text_file = os.path.splitext(image)[0] + '.txt'
        if text_file in text_files:
            shutil.move(os.path.join(dataset_path, text_file), os.path.join(test_folder, text_file))

    for image in valid_images:
        shutil.move(os.path.join(dataset_path, image), os.path.join(valid_folder, image))
        text_file = os.path.splitext(image)[0] + '.txt'
        if text_file in text_files:
            shutil.move(os.path.join(dataset_path, text_file), os.path.join(valid_folder, text_file))

    print("Dataset split into train, test, and valid sets.")

# Example usage
dataset_path = './images'
split_dataset(dataset_path, train_ratio=0.8, test_ratio=0.1, valid_ratio=0.1, seed=42)

