#pragma once

//Defines
#define SafeRelease(x) {if(x) {x->Release(); x = nullptr;} } //Macro for releasing COM objects
#define SafeDelete(x) {if(x) {delete x; x = nullptr;} } //Macro for deleting objects