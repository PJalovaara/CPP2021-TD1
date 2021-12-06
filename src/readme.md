# Source content
This folder should contain only `.cpp` files of your implementation. 
The `.hpp` files are in a separate directory `include`.

A short summary of files in this directory.

**Menu and Level editor** \
`menu.cpp`          (Includes `game.cpp` and `editor.cpp`) \
`editor.cpp`

**Towers** \
`tower.cpp`         (*Abstract base class* `Tower`) \
`basicgoose.cpp`    (Inherits `Tower`) \
`poopergoose.cpp`   (Inherits `Tower`) \
`shotgungoose.cpp`  (Inherits `Tower`) \
`snipergoose.cpp`   (Inherits `Tower`) \
`mamagoose.cpp`     (Inherits `Tower`)

**Build Icon for Towers** \
`buildicon.cpp`

**Enemies** \
`enemy.cpp`         (*Abstract base class* `Enemy`) \
`fyysikko.cpp`      (Inherits `Enemy`) \
`kylteri.cpp`       (Inherits `Enemy`) \
`koneteekkari.cpp`  (Inherits `Enemy`) \
`dokaani.cpp`       (Inherits `Enemy`) \
`cruiseship.cpp`    (Inherits `Enemy`)

**Bullets and Projectiles** \
`bullet.cpp`        (*Base class* `Bullet`) \
`goldenbullet.cpp`  (Inherits `Bullet`) \
`plasmaball.cpp`    (Inherits `Bullet`) \
`poop.cpp`          (Inherits `Bullet`)