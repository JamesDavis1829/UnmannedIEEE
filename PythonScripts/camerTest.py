from SimpleCV import*

cam = Camera()

try:
    while True:
        cam.live()
except KeyboardInterrupt:
    img = cam.getImage()
    img.save("image.bmp")
    print("Done")
