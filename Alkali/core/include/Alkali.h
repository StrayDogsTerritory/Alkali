#ifndef ALK_ALKALI_H
#define ALK_ALKALI_H

#include "system/String.h"
#include "system/SystemTypes.h"
#include "system/MemoryManager.h"
#include "system/Platform.h"
#include "system/MutEx.h"
#include "system/Date.h"
#include "system/FlagBits.h"
#include "system/System.h"
#include "system/LogicTimer.h"
#include "system/Script.h"
#include "system/Thread.h"
#include "system/SHA1.h"
#include "system/SystemInterface.h"
#include "system/Timer.h"


#include "input/Input.h"
#include "input/Action.h"
#include "input/InputEvent.h"
#include "input/InputEventKeyboard.h"
#include "input/InputDevice.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"
#include "input/MouseSDL.h"
#include "input/KeyboardSDL.h"
#include "input/InputInterface.h"
#include "input/InputSDL.h"

#include "graphics/Graphics.h"
#include "graphics/GPUProgram.h"
#include "graphics/GPUProgramGLSL.h"
#include "graphics/Shader.h"
#include "graphics/ShaderGLSL.h"
#include "graphics/GraphicsSDL.h"
#include "graphics/GraphicsInterface.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferGL.h"
#include "graphics/Colour.h"


#include "math/Math.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Plane.h"

#include "gui/Gui.h"

#include "engine/LogWriter.h"
#include "engine/Engine.h"
#include "engine/EngineSDL.h"
#include "engine/EngineSetupInterface.h"
#include "engine/InitVars.h"
#include "engine/Updateable.h"
#include "engine/Updater.h"
#include "engine/ThreadSystem.h"

#include "resources/FileSearcher.h"
#include "resources/ResourceBase.h"
#include "resources/ResourceManager.h"
#include "resources/Resources.h"
#include "resources/ShaderCacher.h"
#include "resources/ShaderManager.h"
#include "resources/ShaderParser.h"

#endif