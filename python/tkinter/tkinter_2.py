import tkinter as tk 

window = tk.Tk()

for font_name in [ "TkDefaultFont", "TkTextFont", "TkFixedFont", "TkMenuFont", "TkHeadingFont", "TkCaptionFont", "TkSmallCaptionFont", "TkIconFont", "TkTooltipFont" ]:
    that_font = tk.font.nametofont(font_name)
    that_font.configure(size=20)
