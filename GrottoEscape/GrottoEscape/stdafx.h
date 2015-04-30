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
#include "SoundManager.h"
#include "Item.h"
#define GRAVITY = 500
#include "utilities\CollisionDetection.h"
#include "managers\ImageManager.h"
#include "managers\SoundManager.h"
#include "GameManager.h"

// TODO: mencionar aquí los encabezados adicionales que el programa necesita
