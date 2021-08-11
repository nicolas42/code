# from https://github.com/enkimute/ganja.js/blob/master/codegen/python/r3.py

def mul(a,b):
    res=[0, 0,0,0, 0,0,0, 0];
    res[0]=b[0]*a[0]+b[1]*a[1]+b[2]*a[2]+b[3]*a[3]-b[4]*a[4]-b[5]*a[5]-b[6]*a[6]-b[7]*a[7]
    res[1]=b[1]*a[0]+b[0]*a[1]-b[4]*a[2]-b[5]*a[3]+b[2]*a[4]+b[3]*a[5]-b[7]*a[6]-b[6]*a[7]
    res[2]=b[2]*a[0]+b[4]*a[1]+b[0]*a[2]-b[6]*a[3]-b[1]*a[4]+b[7]*a[5]+b[3]*a[6]+b[5]*a[7]
    res[3]=b[3]*a[0]+b[5]*a[1]+b[6]*a[2]+b[0]*a[3]-b[7]*a[4]-b[1]*a[5]-b[2]*a[6]-b[4]*a[7]
    res[4]=b[4]*a[0]+b[2]*a[1]-b[1]*a[2]+b[7]*a[3]+b[0]*a[4]-b[6]*a[5]+b[5]*a[6]+b[3]*a[7]
    res[5]=b[5]*a[0]+b[3]*a[1]-b[7]*a[2]-b[1]*a[3]+b[6]*a[4]+b[0]*a[5]-b[4]*a[6]-b[2]*a[7]
    res[6]=b[6]*a[0]+b[7]*a[1]+b[3]*a[2]-b[2]*a[3]-b[5]*a[4]+b[4]*a[5]+b[0]*a[6]+b[1]*a[7]
    res[7]=b[7]*a[0]+b[6]*a[1]-b[5]*a[2]+b[4]*a[3]+b[3]*a[4]-b[2]*a[5]+b[1]*a[6]+b[0]*a[7]
    return res;

def init():
    return [0,0,0,0,0,0,0,0];


def scalar(a):
    return [a,0,0,0,0,0,0,0];


def vector(a):
    return [0,a[0],a[1],a[2],0,0,0,0];


def bivector(a):
    return [0,0,0,0,a[0],a[1],a[2],0];


def trivector(a):
    return [0,0,0,0,0,0,0,a];


from math import *
tau = 2*pi

v = vector([cos(tau/8), sin(tau/8), 0]);
a = vector([cos(tau/8), sin(tau/8), 0]);
b = vector([cos(tau/8)*sin(tau/8), sin(tau/8)*sin(tau/8), cos(tau/8)]);
#multiply([b,a,v,a,b])
ba=mul(b,a); bav=mul(ba,v); bava=mul(bav,a); bavab=mul(bava,b); 

ba=mul(b,a); ab=mul(a,b); bav=mul(ba,v); bavab=mul(bav,ab); 
r=bavab;

