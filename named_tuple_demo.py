from typing import NamedTuple


class SomeType(NamedTuple):
    x: int
    y: int 
    data: bytes
    z: int = 4 

a = SomeType(1, 2, bytes([12,31,23,123,1]) )

print(a)

