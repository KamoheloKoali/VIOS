"""
analyse commands
"""

def analyse_text(text):
    keywords = ["call", "add"]

    for key in keywords:
        if key in text:
            if key == "call":
                pass