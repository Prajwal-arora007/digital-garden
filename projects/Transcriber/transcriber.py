import os
try:
    import streamlit as st
except ModuleNotFoundError:
    raise ModuleNotFoundError("The 'streamlit' module is not installed. Please install it using 'pip install streamlit' before running the script.")

from pytube import YouTube
import whisper
from time import sleep
import numpy as np

# Load the Whisper model
@st.cache_resource
def load_model():
    return whisper.load_model("medium")

# Function to transcribe video with progress
def transcribe_video_with_progress(video_path, model):
    st.write("Preparing transcription...")
    progress_bar = st.progress(0)

    def progress_callback(progress):
        progress_bar.progress(int(progress * 100))

    try:
        result = model.transcribe(video_path, task="translate", verbose=True, progress_callback=progress_callback)
        progress_bar.progress(100)  # Ensure it reaches 100% at the end
        return result['text']
    except RuntimeError as e:
        st.error(f"An error occurred during transcription: {e}")
        return ""

# Streamlit app
def main():
    st.title("AI Video Transcriber")
    st.write("Supports Hindi, English, and Hinglish!")

    model = load_model()

    # Input method selection
    input_method = st.radio("Select video source:", ("Upload Video", "YouTube URL"))

    video_file = None
    if input_method == "Upload Video":
        video_file = st.file_uploader("Upload your video file", type=["mp4", "mkv", "avi"])
    elif input_method == "YouTube URL":
        youtube_url = st.text_input("Enter YouTube video URL")
        if youtube_url:
            try:
                yt = YouTube(youtube_url)
                video_stream = yt.streams.filter(progressive=True, file_extension="mp4").first()
                video_path = video_stream.download(output_path=".", filename="youtube_video.mp4")
                video_file = open(video_path, "rb")
            except Exception as e:
                st.error(f"Error downloading video: {e}")

    if video_file:
        # Save the video to a temporary location
        temp_video_path = f"temp_video.{video_file.name.split('.')[-1]}"
        with open(temp_video_path, "wb") as f:
            f.write(video_file.read())

        st.video(temp_video_path)

        if st.button("Transcribe Video"):
            st.write("Transcribing... This may take some time.")
            transcription = transcribe_video_with_progress(temp_video_path, model)
            if transcription:
                st.subheader("Transcription")
                st.text_area("Transcribed Text", transcription, height=300)

        # Clean up temporary file
        if os.path.exists(temp_video_path):
            os.remove(temp_video_path)

if __name__ == "__main__":
    main()
