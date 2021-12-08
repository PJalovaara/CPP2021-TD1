# Header files
This folder should contain only `.hpp` files of your implementation.
The `.cpp` files are in a separate directory `src`.

A short summary of files in this directory.

**Menu, Game and Level editor** \
`menu.hpp`          (Includes `Game` and `Editor`) \
`game.hpp` \
`editor.hpp`

**Towers** \
`tower.hpp`         (*Abstract base class* `Tower`) \
`basicgoose.hpp`    (Inherits `Tower`) \
`poopergoose.hpp`   (Inherits `Tower`) \
`shotgungoose.hpp`  (Inherits `Tower`) \
`snipergoose.hpp`   (Inherits `Tower`) \
`mamagoose.hpp`     (Inherits `Tower`)

**Build Icon for Towers** \
`buildicon.hpp`     (*Template class*)

**Enemies** \
`enemy.hpp`         (*Abstract base class* `Enemy`) \
`fyysikko.hpp`      (Inherits `Enemy`) \
`kylteri.hpp`       (Inherits `Enemy`) \
`koneteekkari.hpp`  (Inherits `Enemy`) \
`dokaani.hpp`       (Inherits `Enemy`) \
`cruiseship.hpp`    (Inherits `Enemy`)

**Bullets and Projectiles** \
`bullet.hpp`        (*Base class* `Bullet`) \
`goldenbullet.hpp`  (Inherits `Bullet`) \
`plasmaball.hpp`    (Inherits `Bullet`) \
`poop.hpp`          (Inherits `Bullet`)
