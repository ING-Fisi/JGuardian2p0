#ifndef JGUARDIAN_H
#define JGUARDIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "MQTTAsync.h"
#include <iostream>
#include <curl/curl.h>
//#include <string>

#include <stdbool.h>
#include <vector>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
//#include <iio/iio.h>
//#include <iio/iio-debug.h>
#include <sys/time.h>
#include "gpio.h"
//#include <gpiod.hpp>

//#include "json.h"

std::string rsa_priv_key = R"(-----BEGIN PRIVATE KEY-----
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDCFUi+GMO5Ij1J
Z+Pzk7KWgLULSUcpPD8ofT4LJ4+3b0P+XSxuO8p/OzgGIt8mu/mHKxjih1LhhjvC
Mivye9agoYSqhmLrxKlLphoMzikFvozkBDGO92N70KQwegQYxauFQfKTqgGDaN4f
3wqrBak+22OROO+8JiEBI5FqcT7nbGxUtBShMmoym+4L2c3DG0exfNYFhnvHxa15
hvfd8/dM4E/6YyQDvszaopHybx9jxMOMWnuKbaR23pI0JXDLw8zMgcpL/YfXoLKk
8HKvMSRHYWuiyiIz3hdFCtuyIwZd3I34CoLVI7Eq/5x0CHWSkv1L8SnkZSauGt+V
Q/1S3yYZAgMBAAECggEAESHaGZ67wz9Kn+zV7lHUv0yV/qytpY4SCK/Sjt9DhFaj
7sOYiRQJ1mSat87y+hs4hgYnxJJbvnjwFD7DypxEKEqNuJRTjdqes6TyUnxN2noV
O4kDu2oq29qBbd6Nd0bWstUNFdwZVVln1zIkAdAGfjwVTFPVdLs8aVpziwz7V6f+
qX1y3d6V+ZEMG4LZcm+mCzwZr0BrN4HfInrDZXh0yoWZJEeNolcyP4ZIsWQR0odR
PwLH5MHA0l9izv4A0z0EbuKBo6mYvkwQid6VXmSpXX53D35kESVvdN197Yh0B40R
GTpbguGFTzdKTiW2AxtECiOIpjYYqL69ABOc7MkqQQKBgQD/dM6tyYAf4B/XcWmd
TYpbkP2MMsjeEHd4ZhoAUv7UXhMha8a75abDHnphAPAH37/M2MQX7XBcbAK91SV2
NdrNJp64fzd7GJ7bGD5gxnue5Sb965oAdKVbBwq5A417j+dsFVLjj+QB7Aem1kCD
sTC/ZTfBajCLQaPFkczgUGHrWQKBgQDCfwkw3ScMjpxAWhZnrvYkkbrv9ILRgpN1
xcNtvTNU0PKfVOpChQTmoNjPpLEojyi2UsOfsxB41F7YMAkNjaAhjfBHCyFKERMN
T/0BNe6WoRyKNEn3aGOggsqpSFoe75tDHc+771PjUcVieNjTQs67+lA1sYwxI4hJ
uB9KcDN4wQKBgFcNOgUU3nl+SbuEJWZ6bwSnEw/8mmC6IcxAlum3XqmF6WUBMjcD
mmFxeGioBiPYxqaK08AHpLuJ/yErilmPHqG8YGgkygZDrJai21blLGlIU5JCADfZ
iCPN8YR8xnDt6AH3/kgX164j/bOH3XJDJoaCeo6JnkNGOgXwmm1yVvv5AoGAEByf
8UlQs8yYiwgrdPlccJkV6EzUDXEIsCfq0Ytr1inc/2/0XABS8JwAeesFtftt/vSK
Og+GXMwS80u/ZD0IN99fOTNl1ZHmhyLKLbB/DEFacOR2ACXIowJSsYVJ2eg1b3Dn
xYTE6T7b4BVsuMt+/rl0rY4AtA1ie+DhzrPOv8ECgYEAp3c/rGLXahhCWTN4a5T+
wh9fR8XLup/3tdehGQlK1o8LAsRE9f51VrGYPLCF1KDSpdVrMmCEvKMmQiiOLG+8
3lzf0KTtGTpww7Bou/so87IM6HxShw2Peb+xJe3hkzknR3qaPK1oHJAH6F+Rt6wP
/7/pCePtmg3azwuf4/DffIg=
-----END PRIVATE KEY-----)";

std::string rsa_publ_key = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwhVIvhjDuSI9SWfj85Oy
loC1C0lHKTw/KH0+CyePt29D/l0sbjvKfzs4BiLfJrv5hysY4odS4YY7wjIr8nvW
oKGEqoZi68SpS6YaDM4pBb6M5AQxjvdje9CkMHoEGMWrhUHyk6oBg2jeH98KqwWp
PttjkTjvvCYhASORanE+52xsVLQUoTJqMpvuC9nNwxtHsXzWBYZ7x8WteYb33fP3
TOBP+mMkA77M2qKR8m8fY8TDjFp7im2kdt6SNCVwy8PMzIHKS/2H16CypPByrzEk
R2FrosoiM94XRQrbsiMGXdyN+AqC1SOxKv+cdAh1kpL9S/Ep5GUmrhrflUP9Ut8m
GQIDAQAB
-----END PUBLIC KEY-----)";

#endif // JGUARDIAN_H
