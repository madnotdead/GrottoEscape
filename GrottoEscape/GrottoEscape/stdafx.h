// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include "Game.h"
#include <tmx\MapLoader.h>
#include "Player.h"
#include "Slime.h"
#include <SFML\Audio.hpp>
#include <SFML\Audio\Music.hpp>
#include "Item.h"
#include "FireMonster.h"
#define GRAVITY = 500
// TODO: mencionar aquí los encabezados adicionales que el programa necesita
#include "ImageManager.h"
#include "Utils.h"
#include "HealthBar.h"
#include "GameManager.h"
#include "GameStateIntro.h"