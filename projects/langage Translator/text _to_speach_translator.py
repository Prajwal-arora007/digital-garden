import tkinter

import pyttsx3
import speech_recognition as sr
from PIL import ImageTk, Image
from tkinter import *
from translate import Translator






def Translate():
    translator = Translator(from_lang= InputLanguageChoice.get(),to_lang=TranslateLanguageChoice.get())
    Translation = translator.translate(TextVar.get())
    OutputVar.set(Translation)

def text_speech():
    voices = engine.getProperty('voices')
    engine.setProperty('voice', voices[0].id)
    print("here")
    message =TextVar.get()
    print(message)

    engine.say(message)
    engine.runAndWait()

def text_speecho():
    voices = engine.getProperty('voices')
    engine.setProperty('voice', voices[0].id)
    print("here")
    message =OutputVar.get()
    print(message)

    engine.say(message)
    engine.runAndWait()

def SpeakText(command):
    # Initialize the engine

    engine.say(command)
    engine.runAndWait()
    TextBox1.insert(0,command)

def Reset():
    TextBox1.delete(0,30)
    TextBox2.delete(0,30)

def Exit():
    root.destroy()

def speach_text():
    r = sr.Recognizer()
    mic = sr.Microphone(device_index=0)
    try:

        # use the microphone as source for input.
        with sr.Microphone() as source2:

            # wait for a second to let the recognizer
            # adjust the energy threshold based on
            # the surrounding noise level
            r.adjust_for_ambient_noise(source2, duration=0.2)

            # listens for the user's input
            audio2 = r.listen(source2)

            # Using google to recognize audio
            MyText = r.recognize_google(audio2)
            MyText = MyText.lower()

            print("Did you say " + MyText)

            SpeakText(MyText)


    except sr.RequestError as e:
        print("Could not request results; {0}".format(e))

    except sr.UnknownValueError:
        print("unknown error occured")



root = tkinter.Tk()
root.title("Translator")
root.geometry("900x800")
TextVar=StringVar()
engine = pyttsx3.init()

root.title("translator")
root.geometry("900x800")
root.resizable(0,0)
InputLanguageChoice = StringVar()
TranslateLanguageChoice = StringVar()

LanguageChoices = {'Hindi','English','French','German','Spanish'}
InputLanguageChoice.set('English')
TranslateLanguageChoice.set('spanish')


F0=Frame(root)
F0.grid(row=0,column=2)
Label(F0, text="TEXT TRANSLATOR",font=('Arial','20')).grid(row=0, column=3)
F01=Frame(root,height=300,width=10)
F01.grid(row=2,column=0)
F01.pack_propagate(False)
F1=Frame(root,height=300,width=350,highlightbackground="gray",highlightthickness=2)
F1.grid(row=2,column=2)
F1.pack_propagate(False)
F02=Frame(root,height=300,width=40)
F02.grid(row=2,column=3)
F02.pack_propagate(False)
F2=Frame(root,height=300,width=350,highlightbackground="gray",highlightthickness=2)
F2.grid(row=2,column=4)
F2.pack_propagate(False)

InputLanguageChoiceMenu = OptionMenu(F1, InputLanguageChoice, *LanguageChoices)
Label(F1, text="Choose a Language",font="20").grid(row=1, column=0)
InputLanguageChoiceMenu.grid(row=2, column=0)

# choice in which the language is to be translated
NewLanguageChoiceMenu = OptionMenu(F2, TranslateLanguageChoice, *LanguageChoices)
Label(F2, text="Translated Language ",font="20").grid(row=1, column=3)
NewLanguageChoiceMenu.grid(row=2, column=3)
Label(F1, text="Enter Text",font="20").grid(row=3, column=0)

TextBox1 = Entry(F1, textvariable=TextVar,font="20")
TextBox1.grid(row=3, column=2)

Label(F2, text="Output Text", font="20").grid(row=3, column=3)
OutputVar = StringVar()
TextBox2 = Entry(F2, textvariable=OutputVar,font="20")
TextBox2.grid(row=3, column=4)


img=PhotoImage(file='D:\\PycharmProjects\\pythonProject1\\volume1.png',height=50, width=50)
b1=Button(F1,image=img,command=text_speech)
b1.grid(row=5, column=0)
b2=Button(F2,image=img,command=text_speecho)
b2.grid(row=5, column=3)

img1=PhotoImage(file='D:\\PycharmProjects\\pythonProject1\\mike.png',height=50, width=50)
b3=Button(F1,image=img1,command=speach_text)
b3.grid(row=5, column=2)


# Button for calling function
B = Button(root, text="Translate", command=Translate, relief=GROOVE,font="20")
B.grid(row=5, column=2, columnspan=3)
BR= Button(root, text="Reset", command=Reset, relief=GROOVE,font="20")
BR.grid(row=5, column=1, columnspan=3)
BE= Button(root, text="Exit", command=Exit, relief=GROOVE,font="20")
BE.grid(row=5, column=4, columnspan=3)

root.mainloop()


