
# Processes

 2^64 |   pid = 20
      |--------------
      |    stack (vp = 6, pp = 10, flags = private)
      |--------------
      |
      |--------------
      |    heap (vp = 5,  pp = 15, flags = private)
      |--------------
      |
      |--------------
      |    shared (vp = 4,  pp = 18, flags = shared)
      |--------------
      |
      |--------------
      |   .data (vp = 3,  pp = 12, flags = private, r/o, cow)
      |-------------- 
      |   .text (vp = 2,  pp = 13, flags = r/o)
      |--------------
 0    |



 2^64 |   pid = 21
      |--------------
      |    stack (vp = 6, pp = 18, flags = private)
      |--------------
      |
      |--------------
      |    heap (vp = 5,  pp = 11, flags = private)
      |--------------
      |--------------
      |    shared (vp = 4,  pp = 18, flags = shared)
      |--------------
      |--------------
      |   .data (vp = 3,  pp = 12, flags = private, r/o, cow)
      |-------------- 
      |   .text (vp = 2,  pp = 13, flags = r/o)
      |--------------
 0    |

# Threads

 2^64 |   pid = 20
      |--------------
      |    extra stack1 (vp = 7, pp = 11, flags = private)
      |--------------
      |--------------
      |    main stack (vp = 6, pp = 10, flags = private)
      |--------------
      |
      |--------------
      |    heap (vp = 5,  pp = 15, flags = private)
      |--------------
      |
      |--------------
      |   .data (vp = 3,  pp = 12, flags = private, r/o, cow)
      |-------------- 
      |   .text (vp = 2,  pp = 13, flags = r/o)
      |--------------
 0    |



