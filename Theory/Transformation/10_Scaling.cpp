
Scaling:

Scaling changes the size of an object by multiplying each coordinate by a scale factor.

        Model Matrix          Vertex Position    Scaling vertex
        [SX   0   0  0]               [x]           [SX.x]         
        [ 0  SY   0  0]      *        [y]      =    [SY.y] 
        [ 0   0  SZ  0]               [z]           [SZ.z]         
        [ 0   0   0  1]               [1]           [  1 ] 
         ^    ^   ^  ^
         x    y   z  w
         |    |   |  |
      Each column represents how the local basis vectors (X, Y, Z) are transformed.
    
    - Sx, Sy, Sz are the scale factors along the X, Y, and Z axes
    - Each vertex component is scaled independently
    - The w component remains 1 in affine transformations


- Important interpretation
    Each column does NOT represent an axis by itself. Each column describes how a basis vector is transformed