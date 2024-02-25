import os

folder_path = "./"
files = os.listdir(folder_path)
file_pairs = {}

# Separating files into pairs based on the common name
for file in files:
    name, extension = os.path.splitext(file)
    if extension.lower() in ['.jpg', '.txt']:
        base_name = name[:-1] if name.endswith('1') else name
        file_pairs.setdefault(base_name, []).append(file)

# Renaming
for index, (base_name, file_list) in enumerate(file_pairs.items(), start=1):
    for i, file in enumerate(file_list, start=1):
        new_name = f"i{index}_{i}{os.path.splitext(file)[1]}"
        old_path = os.path.join(folder_path, file)
        new_path = os.path.join(folder_path, new_name)
        os.rename(old_path, new_path)

