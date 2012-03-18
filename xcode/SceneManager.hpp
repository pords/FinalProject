#ifndef FinalProject_SceneManager_hpp
#define FinalProject_SceneManager_hpp

#include <vector>
#include "cinder/app/KeyEvent.h"

using namespace ci::app;

class SceneManager {
public:
	class Scene {
		bool m_active, m_loaded;
		friend class SceneManager;
        friend class PauseScene;
		
		SceneManager *m_manager;
		
		virtual void onActivate() {}
		virtual void onDeactivate(SceneManager &sm) {}
	public:
		Scene() : m_active(false), m_loaded(false), m_manager(0) {}
		
		bool isActive() const { return m_active; };
		SceneManager* getManager() const { return m_manager; }
		
		virtual void draw() = 0;
		virtual void update() = 0;
		
		virtual void onKeyUp(KeyEvent &e) {}
		virtual void onKeyDown(KeyEvent &e) {}
        
        virtual void mouseUp(MouseEvent &event){}
        virtual void mouseDown(MouseEvent &event){}
        virtual void mouseMove(MouseEvent &event){}
        virtual void mouseDrag(MouseEvent &event){}
		
        virtual void onLoad(){};
        
		virtual ~Scene() {}
	};
	
	typedef Scene* SceneRef;
	
    int getSize(){
        return m_scenes.size();
    }
	
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
    
    void poppop(int n){
        for( int i = 0; i < n; i++ )
        {
            pop();
        }
    }
    
    void popFront(){
        if ( m_scenes.empty() ) return;
		m_scenes.erase(m_scenes.begin());
    }
	
	SceneRef top() const {
		if ( m_scenes.empty() ) return 0;
		return m_scenes.back();
	}
    
    SceneRef bot() const{
        if(m_scenes.empty()) return 0;
        return m_scenes.front();
    }
	
	void draw() {
		if ( !m_scenes.empty() )
			m_scenes.back()->draw();
	}
	void update() {
		if ( !m_scenes.empty() )
			m_scenes.back()->update();		
	}
	
	void onKeyUp(KeyEvent &e) {
		if ( !m_scenes.empty() )
			m_scenes.back()->onKeyUp(e);
	}
	
	void onKeyDown(KeyEvent &e) {
		if ( !m_scenes.empty() )
			m_scenes.back()->onKeyDown(e);
	}
    
    void mouseDown( MouseEvent &event ) {
        if ( !m_scenes.empty() )
			m_scenes.back()->mouseDown(event);
    }
    
    void mouseUp( MouseEvent &event ){
        if ( !m_scenes.empty() )
			m_scenes.back()->mouseUp(event);
    }
    
    void mouseMove( MouseEvent &event ) {
        if ( !m_scenes.empty() )
			m_scenes.back()->mouseMove(event);
    }
    
    void mouseDrag( MouseEvent &event ) {
        if ( !m_scenes.empty() )
			m_scenes.back()->mouseDrag(event);
    }

	std::vector<SceneRef> m_scenes;
};


#endif
