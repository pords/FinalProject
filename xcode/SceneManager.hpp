#ifndef FinalProject_SceneManager_hpp
#define FinalProject_SceneManager_hpp

#include <vector>
#include "cinder/app/KeyEvent.h"

class SceneManager {
public:
	class Scene {
		bool m_active, m_loaded;
		friend class SceneManager;
		
		SceneManager *m_manager;
		
		virtual void onActivate() {}
		virtual void onDeactivate(SceneManager &sm) {}
	public:
		Scene() : m_active(false), m_loaded(false), m_manager(0) {}
		
		bool isActive() const { return m_active; };
		SceneManager* getManager() const { return m_manager; }
		
		virtual void draw() = 0;
		virtual void update() = 0;
		
		virtual void onKeyUp(ci::app::KeyEvent &e) {}
		virtual void onKeyDown(ci::app::KeyEvent &e) {}
		
        virtual void onLoad(){};
        
		virtual ~Scene() {}
	};
	
	typedef Scene* SceneRef;
	
	
	void push(SceneRef s) {
		if ( !m_scenes.empty() ) {			
			SceneRef prev = m_scenes.back();
			prev->m_active = false;
			prev->onDeactivate(*this);
		}
		m_scenes.push_back(s);
		s->m_manager = this;
		s->m_active = true;
        if( !s->m_loaded ){
            s->onLoad();
            s->m_loaded = true;
        }
		s->onActivate();
	}
	
	void pop() {
		if ( m_scenes.empty() ) return;
		SceneRef prev = m_scenes.back();
		m_scenes.pop_back();
		prev->m_active = false;
		prev->m_manager = 0;
		prev->onDeactivate(*this);
		
		if ( m_scenes.empty() ) return;
		prev = m_scenes.back();
		prev->m_active = true;
		prev->onActivate();
	}
	
	SceneRef top() const {
		if ( m_scenes.empty() ) return 0;
		return m_scenes.back();
	}
	
	void draw() {
		if ( !m_scenes.empty() )
			m_scenes.back()->draw();
	}
	void update() {
		if ( !m_scenes.empty() )
			m_scenes.back()->update();		
	}
	
	void onKeyUp(ci::app::KeyEvent &e) {
		if ( !m_scenes.empty() )
			m_scenes.back()->onKeyUp(e);
	}
	
	void onKeyDown(ci::app::KeyEvent &e) {
		if ( !m_scenes.empty() )
			m_scenes.back()->onKeyDown(e);
	}

	
private:
	std::vector<SceneRef> m_scenes;
};


#endif
