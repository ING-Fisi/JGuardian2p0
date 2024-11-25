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
#include "Logger.h"

//std::string rsa_priv_key = R"(-----BEGIN PRIVATE KEY-----
//MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDCFUi+GMO5Ij1J
//Z+Pzk7KWgLULSUcpPD8ofT4LJ4+3b0P+XSxuO8p/OzgGIt8mu/mHKxjih1LhhjvC
//Mivye9agoYSqhmLrxKlLphoMzikFvozkBDGO92N70KQwegQYxauFQfKTqgGDaN4f
//3wqrBak+22OROO+8JiEBI5FqcT7nbGxUtBShMmoym+4L2c3DG0exfNYFhnvHxa15
//hvfd8/dM4E/6YyQDvszaopHybx9jxMOMWnuKbaR23pI0JXDLw8zMgcpL/YfXoLKk
//8HKvMSRHYWuiyiIz3hdFCtuyIwZd3I34CoLVI7Eq/5x0CHWSkv1L8SnkZSauGt+V
//Q/1S3yYZAgMBAAECggEAESHaGZ67wz9Kn+zV7lHUv0yV/qytpY4SCK/Sjt9DhFaj
//7sOYiRQJ1mSat87y+hs4hgYnxJJbvnjwFD7DypxEKEqNuJRTjdqes6TyUnxN2noV
//O4kDu2oq29qBbd6Nd0bWstUNFdwZVVln1zIkAdAGfjwVTFPVdLs8aVpziwz7V6f+
//qX1y3d6V+ZEMG4LZcm+mCzwZr0BrN4HfInrDZXh0yoWZJEeNolcyP4ZIsWQR0odR
//PwLH5MHA0l9izv4A0z0EbuKBo6mYvkwQid6VXmSpXX53D35kESVvdN197Yh0B40R
//GTpbguGFTzdKTiW2AxtECiOIpjYYqL69ABOc7MkqQQKBgQD/dM6tyYAf4B/XcWmd
//TYpbkP2MMsjeEHd4ZhoAUv7UXhMha8a75abDHnphAPAH37/M2MQX7XBcbAK91SV2
//NdrNJp64fzd7GJ7bGD5gxnue5Sb965oAdKVbBwq5A417j+dsFVLjj+QB7Aem1kCD
//sTC/ZTfBajCLQaPFkczgUGHrWQKBgQDCfwkw3ScMjpxAWhZnrvYkkbrv9ILRgpN1
//xcNtvTNU0PKfVOpChQTmoNjPpLEojyi2UsOfsxB41F7YMAkNjaAhjfBHCyFKERMN
//T/0BNe6WoRyKNEn3aGOggsqpSFoe75tDHc+771PjUcVieNjTQs67+lA1sYwxI4hJ
//uB9KcDN4wQKBgFcNOgUU3nl+SbuEJWZ6bwSnEw/8mmC6IcxAlum3XqmF6WUBMjcD
//mmFxeGioBiPYxqaK08AHpLuJ/yErilmPHqG8YGgkygZDrJai21blLGlIU5JCADfZ
//iCPN8YR8xnDt6AH3/kgX164j/bOH3XJDJoaCeo6JnkNGOgXwmm1yVvv5AoGAEByf
//8UlQs8yYiwgrdPlccJkV6EzUDXEIsCfq0Ytr1inc/2/0XABS8JwAeesFtftt/vSK
//Og+GXMwS80u/ZD0IN99fOTNl1ZHmhyLKLbB/DEFacOR2ACXIowJSsYVJ2eg1b3Dn
//xYTE6T7b4BVsuMt+/rl0rY4AtA1ie+DhzrPOv8ECgYEAp3c/rGLXahhCWTN4a5T+
//wh9fR8XLup/3tdehGQlK1o8LAsRE9f51VrGYPLCF1KDSpdVrMmCEvKMmQiiOLG+8
//3lzf0KTtGTpww7Bou/so87IM6HxShw2Peb+xJe3hkzknR3qaPK1oHJAH6F+Rt6wP
///7/pCePtmg3azwuf4/DffIg=
//-----END PRIVATE KEY-----)";

//std::string rsa_publ_key = R"(-----BEGIN PUBLIC KEY-----
//MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwhVIvhjDuSI9SWfj85Oy
//loC1C0lHKTw/KH0+CyePt29D/l0sbjvKfzs4BiLfJrv5hysY4odS4YY7wjIr8nvW
//oKGEqoZi68SpS6YaDM4pBb6M5AQxjvdje9CkMHoEGMWrhUHyk6oBg2jeH98KqwWp
//PttjkTjvvCYhASORanE+52xsVLQUoTJqMpvuC9nNwxtHsXzWBYZ7x8WteYb33fP3
//TOBP+mMkA77M2qKR8m8fY8TDjFp7im2kdt6SNCVwy8PMzIHKS/2H16CypPByrzEk
//R2FrosoiM94XRQrbsiMGXdyN+AqC1SOxKv+cdAh1kpL9S/Ep5GUmrhrflUP9Ut8m
//GQIDAQAB
//-----END PUBLIC KEY-----)";



std::string rsa_priv_key = R"(-----BEGIN PRIVATE KEY-----
MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQC46OglMnP3nDvh
/13d0nlDS8kMIbFAE44RsrMcEcXmOHWMaFNmw8IoiP+sQ7Z6M/fin0U7MdJ13je4
JzVOKMrO+kvkakvWzt0cJvGikO8yA82a5vWAi3at/t4+9Tzb5b8su1kj+6Au7WFi
pO8LjODUjLZhjifz7IiGxImxhxfq9CRg9AK1Gq+KH/yUoBUqatHELjg5ZUF/9jmB
pfgFST9dXSlaXmwgtW75IYiukdIfDj0Ilg+aUwJLWUdLGr0qzrKrp8w78XCehctr
C1Al1/OK/3HsHb5pvcFvG+WnSL3qVSmlbjNCtDr785JXedokxGRa72V/GjnRYEYg
SzFWeo5rAgMBAAECggEAANgaQLmiMCPMx6JLPx2aQ3acMaYjukXvVum5QzljIjFS
7fyzUZljA19t+vbHI11NZ+dLYBUQirZ8zi8WrG8aYNFYoxu+tQ+z+mZjmM4jGSMP
wY8FXYU6cAIeomoVRCoBf5O6e2Y1oFxAnsCdWiOT8BR4lDJdrw0rGB2VIcFCoUvM
ryle4dEbhM4ArHlMkhAHakV5LsfN0bsL9UUOWXDz1qngAaoyI5pgxG4L0JvocSNY
XG/EV1/HBzAebDWdMf/bX3WzH5L+HOTrWqIMQjAIkHSH/jpsjMob25OG3/W4wUG+
81G7fSPqPkCdSZDd6Uf1bqPOC7Xx0BFdsbU5XiRWWQKBgQD6TKlHuTFhTmWLvIi4
Z+LMyHmtv5KJx9VI3FejAN4Z7CC1acojkfOaJgnDIaz3b9lr5iJnDJ5H6zg+lGsm
4BQmZ/2/7+FYTL6QPk9UJhvSObSpf97/ZZhr/UE2JANfxxI3bSeVS58k6KBjdn3P
497UrQhbxMnktojgeKcqFmIXOQKBgQC9Hv/iFHuwDvc1xAlPO25tndABS+jz7I5B
vCU/bASN2YQMedceI6d578Tf4jGoB3nBjQhCLuxAZuhRvOUOz6m4pi2klrqx7kKG
z2uSpEU3TvfQnBlvZC51Jtkayh5L4LZaxiRCqux723JDGQezBzjzneocJ7JyKBk0
fs1QmKvOwwKBgQDSBad5LlTX8F9WjEEwcsMk0AcBmqDMCajWtUS32s+CctbTQkxB
4oLEUqyYVlZ7XRfT6MvvKfBaKm4MXJ84hIeD3nhWKGMuo163TAFme3+Wu6LzIv+r
z8TAwEWKt1c5c6G+blHrfQOxhZynONLCsNLWI8bCsfIyflOF/tdNgnCWSQKBgQCa
4FYhKTEZv0fH6iDNmBgZANIlHatKhwEA6DmAtM8N84HmTalTb1Np0mdiCXUs6+JU
FVEcEh07qIq81XqoJHwTUVOzpBSEPmCQ0jCASLK+VpcvaYaS6HH7UrMc80TYUtBD
ilyLlDpSPCZYuJjLjjCfoUTlhcTnI9twWB9/z2dzzQKBgQCKu3YIfWMpHjT1GMt/
uDq7AgwkJzsiTwGdgP4fjnCRx5O5wfeSMKWKzz6Sn1z/zQXyBNgB5cy2XrzuGytx
Y5uyzoVhW3z6ZsH9AsNVLPgIz2GSf8/SzPQ52B/g2e0rs8AvYLWaoMJYjfs6iT/W
yWJpFXChbahSjLsfzE8VtJiQkA==
-----END PRIVATE KEY-----)";

std::string rsa_publ_key = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuOjoJTJz95w74f9d3dJ5
Q0vJDCGxQBOOEbKzHBHF5jh1jGhTZsPCKIj/rEO2ejP34p9FOzHSdd43uCc1TijK
zvpL5GpL1s7dHCbxopDvMgPNmub1gIt2rf7ePvU82+W/LLtZI/ugLu1hYqTvC4zg
1Iy2YY4n8+yIhsSJsYcX6vQkYPQCtRqvih/8lKAVKmrRxC44OWVBf/Y5gaX4BUk/
XV0pWl5sILVu+SGIrpHSHw49CJYPmlMCS1lHSxq9Ks6yq6fMO/FwnoXLawtQJdfz
iv9x7B2+ab3Bbxvlp0i96lUppW4zQrQ6+/OSV3naJMRkWu9lfxo50WBGIEsxVnqO
awIDAQAB
-----END PUBLIC KEY-----)";



#endif // JGUARDIAN_H
