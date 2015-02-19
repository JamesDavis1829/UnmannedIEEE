from SimpleCV import*
import time

cam = Camera(0,{"width": 640,"height": 360})

try:
    while True:
        img = cam.getImage()
        lines = img.findLines(threshold = 80, minlinelength = 50)
        x=0
        print(lines[0])
        while(x<len(lines)):
             lines[x] = lines[x].extendToImageEdges()
             avg=lines[x].angle()
             x=x+1
        y = 0
        Horizontal = [Line(img,((0,0),(0,0)))]
        Vertical = [Line(img,((0,0),(0,0)))]
        for y in range(-1,x):
            if lines[y].angle() < 45:
                Horizontal.append(lines[y])
            if lines[y].angle() > 45:
                Vertical.append(lines[y])
        Horizontal.pop(0)
        Vertical.pop(0)
        H_Counter=0
        V_Counter=0
        interSectionPoints = [(0,0)]
        while(H_Counter<len(Horizontal)):
            while(V_Counter<len(Vertical)):
                interSectionPoints.append(Horizontal[H_Counter].findIntersection(Vertical[V_Counter]))
                V_Counter=V_Counter+1
            H_Counter=H_Counter+1
        interSectionPoints.pop(0)
        
        avg=avg/x
        x=0
        while(x<len(interSectionPoints)):
            img.dl().circle(interSectionPoints[x],10,Color.RED)
            x=x+1
        lines.draw(width = 3)
        #print("\n\n this is the average\n\n")
        print ("\n\n")
        print("HORIZONTAL:")
        print(Horizontal)
        print("\n\n")
        print("VERTICAL:")
        print(Vertical)
        print("\n\n")
        print("POINTS:")
        print(interSectionPoints)
        img.show()
        
        time.sleep(3)
except KeyboardInterrupt:
    print("Done")
