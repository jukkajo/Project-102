import os

folder_path = "./images"
files = os.listdir(folder_path)
file_pairs = {}

# Separating files into pairs based on the common name
for file in files:
    name, extension = os.path.splitext(file)
    if extension.lower() in ['.jpg', '.txt']:
        base_name = name
        file_pairs.setdefault(base_name, []).append(extension)

# Renaming
for index, (base_name, extension_list) in enumerate(file_pairs.items(), start=1):
    new_name = f"i{index}"
    
    for extension in extension_list:
        old_path = os.path.join(folder_path, f"{base_name}{extension}")
        new_path = os.path.join(folder_path, f"{new_name}{extension}")
        os.rename(old_path, new_path)

