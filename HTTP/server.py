from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    return "Hello, World!"

if __name__ == '__main__':
    app.run(debug=True)


# to run this code in terminal write:
# python server.py
# or:
# right click hear and RUN python -> run python file in terminal

# after thet you can see URL in terminal then copy it in webbrowser the u should see 
# HELLO world! in http */