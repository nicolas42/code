import tkinter

def tkinter_demo():
    global window, lbl, btn

    window = tkinter.Tk()
    window.title("Welcome to LikeGeeks app")
    window.geometry('350x200')

    font=("Arial Bold", 50)

    lbl = tkinter.Label(window, text="Hello", font=font)
    lbl.grid(column=0, row=0)
    btn = tkinter.Button(window, text="Click Me", font=font, height = 100, width = 100)
    btn.grid(column=1, row=0)
    window.mainloop()


if __name__ == "__main__":
    tkinter_demo()

