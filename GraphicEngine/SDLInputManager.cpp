#include "SDLInputManager.h"


SDLInputManager::SDLInputManager()
{
	m_keyPressed = new bool[IM_KEY_LAST];
	m_mouseButtonPressed = new bool[IM_MOUSE_LAST];

	for (unsigned int i = 0; i < IM_KEY_LAST; ++i)
	{
		m_keyPressed[i] = false;
	}
	
	for (unsigned int i = 0; i < IM_MOUSE_LAST; ++i)
	{
		m_mouseButtonPressed[i] = false;
	}

	m_eventMasks.push_back(SDL_EventType::SDL_KEYDOWN);
	m_eventMasks.push_back(SDL_EventType::SDL_KEYUP);
	m_eventMasks.push_back(SDL_EventType::SDL_MOUSEBUTTONDOWN);
	m_eventMasks.push_back(SDL_EventType::SDL_MOUSEBUTTONUP);
	m_eventMasks.push_back(SDL_EventType::SDL_MOUSEMOTION);
}


SDLInputManager::~SDLInputManager()
{
	delete[] m_keyPressed;
	delete[] m_mouseButtonPressed;
}

void SDLInputManager::initialize()
{
	s_instance = new SDLInputManager();
}

bool SDLInputManager::isKeyDown(KeyId _keyId)
{
	if (_keyId < IM_KEY_LAST)
		return m_keyPressed[_keyId];

	return false;
}

bool SDLInputManager::isKeyUp(KeyId _keyId)
{
	if (_keyId < IM_KEY_LAST)
		return !m_keyPressed[_keyId];

	return false;
}

bool SDLInputManager::isMouseButtonDown(MouseButtonId _mouseId)
{
	if (_mouseId < IM_MOUSE_LAST)
		return m_mouseButtonPressed[_mouseId];

	return false;
}

bool SDLInputManager::isMouseButtonUp(MouseButtonId _mouseId)
{
	if (_mouseId < IM_MOUSE_LAST)
		return !m_mouseButtonPressed[_mouseId];

	return false;
}

MouseMotion& SDLInputManager::getMouseMotion()
{
	return m_mouseMotion;
}

void SDLInputManager::resetMouseMotion()
{
	m_mouseMotion.dx = 0;
	m_mouseMotion.dy = 0;
}

void SDLInputManager::handleEvent(SDL_Event& _event)
{
	KeyId keyId;
	SDL_Keycode sdlk;
	Uint8 mouseButton;
	MouseButtonId mouseButtonId;

	switch (_event.type)
	{
	case SDL_KEYDOWN:
		sdlk = _event.key.keysym.sym;
		keyId = SDLKeyToKeyId(sdlk);
		m_keyPressed[keyId] = true;
		break;

	case SDL_KEYUP:
		sdlk = _event.key.keysym.sym;
		keyId = SDLKeyToKeyId(sdlk);
		m_keyPressed[keyId] = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		mouseButton = _event.button.button;
		mouseButtonId = SDLMouseButtonToMouseButtonId(mouseButton);
		m_mouseButtonPressed[mouseButtonId] = true;
		break;

	case SDL_MOUSEBUTTONUP:
		mouseButton = _event.button.button;
		mouseButtonId = SDLMouseButtonToMouseButtonId(mouseButton);
		m_mouseButtonPressed[mouseButtonId] = false;
		break;

	case SDL_MOUSEMOTION:
		m_mouseMotion.x = _event.motion.x;
		m_mouseMotion.y = _event.motion.y;
		m_mouseMotion.dx = _event.motion.xrel;
		m_mouseMotion.dy = _event.motion.yrel;

		break;
	}
}

std::vector<SDL_EventType>& SDLInputManager::getMasks()
{
	return m_eventMasks;
}

KeyId SDLInputManager::SDLKeyToKeyId(SDL_Keycode _sdlk)
{
	switch (_sdlk)
	{
	case SDLK_0:
		return IM_KEY_0;
	case SDLK_1:
		return IM_KEY_1;
	case SDLK_2:
		return IM_KEY_2;
	case SDLK_3:
		return IM_KEY_3;
	case SDLK_4:
		return IM_KEY_4;
	case SDLK_5:
		return IM_KEY_5;
	case SDLK_6:
		return IM_KEY_6;
	case SDLK_7:
		return IM_KEY_7;
	case SDLK_8:
		return IM_KEY_8;
	case SDLK_9:
		return IM_KEY_9;

	case SDLK_a:
		return IM_KEY_A;
	case SDLK_b:
		return IM_KEY_B;
	case SDLK_c:
		return IM_KEY_C;
	case SDLK_d:
		return IM_KEY_D;
	case SDLK_e:
		return IM_KEY_E;
	case SDLK_f:
		return IM_KEY_F;
	case SDLK_g:
		return IM_KEY_G;
	case SDLK_h:
		return IM_KEY_H;
	case SDLK_i:
		return IM_KEY_I;
	case SDLK_j:
		return IM_KEY_J;
	case SDLK_k:
		return IM_KEY_K;
	case SDLK_l:
		return IM_KEY_L;
	case SDLK_m:
		return IM_KEY_M;
	case SDLK_n:
		return IM_KEY_N;
	case SDLK_o:
		return IM_KEY_O;
	case SDLK_p:
		return IM_KEY_P;
	case SDLK_q:
		return IM_KEY_Q;
	case SDLK_r:
		return IM_KEY_R;
	case SDLK_s:
		return IM_KEY_S;
	case SDLK_t:
		return IM_KEY_T;
	case SDLK_u:
		return IM_KEY_U;
	case SDLK_v:
		return IM_KEY_V;
	case SDLK_w:
		return IM_KEY_W;
	case SDLK_x:
		return IM_KEY_X;
	case SDLK_y:
		return IM_KEY_Y;
	case SDLK_z:
		return IM_KEY_Z;

	case SDLK_UP:
		return IM_KEY_UP;
	case SDLK_DOWN:
		return IM_KEY_DOWN;
	case SDLK_LEFT:
		return IM_KEY_LEFT;
	case SDLK_RIGHT:
		return IM_KEY_RIGHT;

	case SDLK_ESCAPE:
		return IM_KEY_ESCAPE;

	case SDLK_F1:
		return IM_KEY_F1;
	case SDLK_F2:
		return IM_KEY_F2;
	case SDLK_F3:
		return IM_KEY_F3;
	case SDLK_F4:
		return IM_KEY_F4;
	case SDLK_F5:
		return IM_KEY_F5;
	case SDLK_F6:
		return IM_KEY_F6;
	case SDLK_F7:
		return IM_KEY_F7;
	case SDLK_F8:
		return IM_KEY_F8;
	case SDLK_F9:
		return IM_KEY_F9;
	case SDLK_F10:
		return IM_KEY_F10;
	case SDLK_F11:
		return IM_KEY_F11;
	case SDLK_F12:
		return IM_KEY_F12;


	default:
		LogManager::showError("Unable to handle entered key.");
		return IM_KEY_0;
	}
}

MouseButtonId SDLInputManager::SDLMouseButtonToMouseButtonId(Uint8 _sdlMouseButton)
{
	switch (_sdlMouseButton)
	{
	case SDL_BUTTON_LEFT:
		return IM_MOUSE_LEFT;
	case SDL_BUTTON_RIGHT:
		return IM_MOUSE_RIGHT;
	case SDL_BUTTON_MIDDLE:
		return IM_MOUSE_MIDDLE;

	default:
		LogManager::showError("Unable to handle mouse button.");
		return IM_MOUSE_LEFT;
	}
}