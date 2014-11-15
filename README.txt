This package provides class to control the GPIO on Allwinner sunxi platform.

First of all,you should make sure your script.fex had modified and generate script.bin

This project is only for sunxi soc,and just for gpio input output
Example
=======

Typical usage::
    
    #!/usr/bin/env python

    import SUNXI_GPIO as GPIO

    #init module
    GPIO.init()
    
    #configure module
    GPIO.setcfg(GPIO.PIN#, GPIO.OUT)
    GPIO.setcfg(GPIO.PIN#, GPIO.IN)
        
    #read the current GPIO configuration
    config = GPIO.getcfg(GPIO.PIN#)
    
    #set GPIO high
    GPIO.output(GPIO.PIN#, GPIO.HIGH)
    
    #set GPIO low
    GPIO.output(GPIO.PIN#, GPIO.LOW)
    
    #read input
    state = GPIO.input(GPIO.PIN#)
    
    #cleanup 
    GPIO.cleanup()

Real examples:

    import SUNXI_GPIO as GPIO
    import time

    LED = GPIO.PD0

    GPIO.init()
    GPIO.setcfg(LED, GPIO.OUT)
       
    while True:
            GPIO.output(LED, GPIO.HIGH)
            time.sleep(1)
            GPIO.output(LED, GPIO.LOW)
            time.sleep(1)
