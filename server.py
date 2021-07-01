from flask import Flask , render_template
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address
app=Flask(__name__)

limiter = Limiter(
    app,
    key_func=get_remote_address,
    default_limits=["200 per day", "20 per minute"]
)

# f=open("userlist.txt","w+")

@app.route('/')
def welcomepage():
    return "hello! You have reached the homepage of our very simple backend database running on \n<br> python and flask,To know usage , read the comment in database.c client files in \n <br>https://www.github.com/NavinShrinivas/perf-test"


@app.route('/makeuser/<username>/<password>')
@limiter.limit("5 per minute")
def newuser(username,password):
    f=open("userlist.txt","r")
    for each in f:
        data=each.split(" ")
        if(username==data[0]):
            return "Account with this username exist!Please select another username."
    f.close()
    f=open("userlist.txt","a")
    account=username+" "+password+"\n"
    f.write(account)
    f.close()
    f=open(username+".txt","w+")
    f.close()
    return "Account created with database access name : %s" % username

@app.route("/write/<username>/<password>/<data>")
@limiter.limit("20 per minute")
def writefn(username,password,data):
    flag=0
    f=open("userlist.txt","r")
    for each in f:
        eachn=each.rstrip()
        udata=eachn.split(" ")
        if(username==udata[0] and password==udata[1]):
            flag=1
    f.close()
    if flag==0:
        return "invalid username or password! If you dont have an account please create one."
    else:
        f=open(username+".txt","a")
        f.write(str(data)+"\n")
        return "True \n<br>Data written to databse."

@app.route("/read/<username>/<password>")
@limiter.limit("20 per minute")
def readfn(username,password):
    flag=0
    f=open("userlist.txt","r")
    for each in f:
        eachn=each.rstrip()
        udata=eachn.split(" ")
        if(username==udata[0] and password==udata[1]):
            flag=1
    f.close()
    if flag==0:
        return "invalid username or password! If you dont have an account please create one."
    else:
        with open(username+".txt","r") as f:
            return render_template('read.html',text=f.read())



if __name__=='__main__':
    app.run("0.0.0.0","3000")
