import tkinter as tk
from tkinter import filedialog, scrolledtext
import os

def grep_query():
    query = entry_query.get()
    directory = filedialog.askdirectory()
    if not query or not directory:
        return

    text_area.configure(state='normal')
    text_area.delete(1.0, tk.END)
    
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    for i, line in enumerate(f, 1):
                        if query in line:
                            result = f"{file_path}:{i}:{line.strip()}\n"
                            text_area.insert(tk.END, result)
            except Exception as e:
                continue
    
    text_area.configure(state='disabled')

app = tk.Tk()
app.title("Simple Grep GUI")

label_query = tk.Label(app, text="Enter Query:")
label_query.pack()

entry_query = tk.Entry(app, width=50)
entry_query.pack()

button_grep = tk.Button(app, text="Select Directory and Grep", command=grep_query)
button_grep.pack()

text_area = scrolledtext.ScrolledText(app, width=60, height=20, state='disabled')
text_area.pack()

app.mainloop()










