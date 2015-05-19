// stdafx.h: archivo de inclusi�n de los archivos de inclusi�n est�ndar del sistema
// o archivos de inclusi�n espec�ficos de un proyecto utilizados frecuentemente,
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
// TODO: mencionar aqu� los encabezados adicionales que el programa necesita
#include "ImageManager.h"
#include "Utils.h"
#include "HealthBar.h"
#include "GameManager.h"
#include "GameStateIntro.h"