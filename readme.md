# SimpleDB
This code was written to be used as a really simpe backend for perf-test project of CS152 CLab project.This was made instead of simply using mongdb atlas becuase using atlas need the libmongoc drivers , which when it comes to portability and running flawlessly on both platforms (Win and Linux) highly lags behind.
# Usage
Clone this repo to your server and run server.py and open up the port 3000 (This is randomised ,you can change this value in server.py file).Also clone this repo to your client side program and import the respective driver from the driver folder.Read below for more instructions.

# Drivers:
Suppported languages/drivers:

* ```C - LibSimpleDBc : Import the h file to your program , this driver is simple single header file driver , NO DEPENDENDIES whatsoever.```

As of now using these drivvers as needed by the developer ofc needs some technical know-how , this is something I can definetly work on.

Hopefully some one can come along and write driver files for other languages , I will see what languages I can add for!