import streamlit as st
from PIL import Image
import pillow_heif
import os
import io
import zipfile

# Register HEIC format with Pillow
pillow_heif.register_heif_opener()

# Function to resize and convert images losslessly
def resize_and_convert_to_jpg_lossless(images, max_width, max_height):
    converted_images = []
    for image in images:
        try:
            # Open image
            img = Image.open(image)
            
            # Resize if larger than max dimensions
            if img.width > max_width or img.height > max_height:
                img.thumbnail((max_width, max_height))
            
            # Convert to RGB for compatibility with JPG
            img = img.convert("RGB")
            
            # Save to a BytesIO stream with 100% quality (lossless for JPG)
            img_io = io.BytesIO()
            img.save(img_io, format="JPEG", quality=100)  # Lossless JPG conversion
            img_io.seek(0)
            
            # Append converted image (name, BytesIO)
            converted_images.append((os.path.splitext(image.name)[0] + ".jpg", img_io))
        except Exception as e:
            st.error(f"Error processing file {image.name}: {e}")
    return converted_images

# Streamlit app interface
st.title("Batch Image Converter to JPG (Lossless Compression)")
st.write("Upload images (up to 50 per batch), resize them, and convert to `.jpg` format with lossless compression.")

# File uploader
uploaded_files = st.file_uploader(
    "Choose images (PNG, BMP, TIFF, HEIC, etc.)", 
    type=["png", "bmp", "tiff", "jpeg", "jpg", "heic"], 
    accept_multiple_files=True
)

# Resize settings
st.sidebar.title("Resize Settings")
max_width = st.sidebar.number_input("Maximum Width (px)", min_value=100, max_value=5000, value=1920, step=50)
max_height = st.sidebar.number_input("Maximum Height (px)", min_value=100, max_value=5000, value=1080, step=50)

if uploaded_files:
    # Enforce a cap of 50 images
    if len(uploaded_files) > 50:
        st.error("You can upload a maximum of 50 images per batch.")
    else:
        st.success(f"{len(uploaded_files)} image(s) uploaded. Ready to convert and resize!")
        
        if st.button("Convert and Resize (Lossless)"):
            converted_files = resize_and_convert_to_jpg_lossless(uploaded_files, max_width, max_height)
            
            if converted_files:
                # Create a ZIP archive of the converted images
                zip_buffer = io.BytesIO()
                with zipfile.ZipFile(zip_buffer, "w") as zipf:
                    for file_name, file_io in converted_files:
                        zipf.writestr(file_name, file_io.getvalue())
                
                zip_buffer.seek(0)
                
                # Offer the ZIP file for download
                st.success("Conversion and resizing complete! Download your images below.")
                st.download_button(
                    label="Download ZIP",
                    data=zip_buffer,
                    file_name="resized_images_lossless.zip",
                    mime="application/zip"
                )
