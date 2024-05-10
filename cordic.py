import math

def main():


        angles = []
        M = float(1e18) # multiplier
        N = int(60)
        for i in range(N):
                angles.append(int(M*math.atan(math.pow(2, -float(i)))))

        print(angles)
        print()

        
        print("x \t y \t cordicAtan2 \t math.Atan2 \t Error")
        maxError = float(1e9)
        for i in range(360):
                a = i*math.pi/180
                x = int(M*math.cos(a))
                y = int(M*math.sin(a))
                
                b = cordicAtan2(y,x)
                c = math.atan2(float(y),float(x))
                # error between b and c
                d = float(b)/M -c 
                # fmt.Printf("%.16X \t %.16X \t %v \t %v \t %v \n", x,y,b,c,d)
                print(x,y,b,c,d)
                
                if d < maxError:  maxError = d 
                
        
        print("Maximum Error", maxError )



def cordicAtan2(y, x):
        return cordicAtan2v(y,x,False)


def cordicAtan2v(y, x , verbose ):
        # return M*atan2(y,x) 
        # todo: if x=0 or y=0 return appropriate angles
        
        # make angles
        angles = []
        M = float(1e18) # multiplier
        N = 60
        for i in range(N):
                angles.append(int(M*math.atan(math.pow(2, -float(i)))))
        

        # get absolute values of inputs
        x0, y0 = int(0), int(0)
        if x<0:
            x0=-x
        else:
            x0=x
        if y<0:
            y0=-y
        else:
            y0=y
        
        newx, newy = int(0), int(0)
        angle = int(0)  
        if verbose==True:
            print("x,y,angle", x,y,angle)
        for i in range(N):
                if y0 > 0:
                        # rotate clockwise (negate)
                        newx = x0 + (y0 >> int(i))
                        newy = -(x0 >> int(i)) + y0
                        angle += angles[int(i)]

                elif y0 < 0:
                        # rotate counterclockwise
                        newx = x0 - (y0 >> int(i))
                        newy = +(x0 >> int(i)) + y0
                        angle -= angles[int(i)]
                
                x0 = newx
                y0 = newy
                if verbose==True:
                    print("x,y,angle", x,y,angle)

        

        result = int(0)
        if x>0 and y>0:
            result = angle
        elif x<0 and y>0:
            result = int(3.1415926535897*M) - angle
        elif x<0 and y<0: 
            result = -int(3.1415926535897*M) + angle
        elif x>0 and y<0:
            result = - angle
        elif x>0 and y==0: 
            result = int(0); print("Oh noes")
        elif x==0 and y>0:
            result = int(3.1415926535897/2*M); print("Oh noes")
        elif x<0 and y==0: 
            result = int(3.1415926535897*M); print("Oh noes")
        elif x==0 and y<0:
            result = int(-3.1415926535897/2*M); print("Oh noes")
        elif x==0 and y==0: 
            print("Oh noes")
            result = angle


        return result


if __name__ == "__main__":
    main()


