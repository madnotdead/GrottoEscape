#ifndef GAME_RESOURCEMANAGER_H_INCLUDED
#define GAME_RESOURCEMANAGER_H_INCLUDED

#include "../utilities/Types.h"
#include <map>
#include <string>

namespace Game
{
	template< class T >
	class ResourceManager 
	{
	public:
		typedef std::pair< std::string, T* > Resource;
		typedef std::map< std::string, T* > ResourceMap;

	private:
		ResourceManager(const ResourceManager& resourceManager);
		ResourceManager& operator=(const ResourceManager& resourceManager);

		ResourceMap mResource;

		T* find(const std::string& strId) 
		{
			T *resource = 0;

			typename ResourceMap::iterator it = mResource.find( strId );
			if(it != mResource.end())
				resource = it->second;

			return resource;
		}

	protected:
		virtual T* load(const std::string& strId) = 0;

	public:
		ResourceManager() {}

		virtual ~ResourceManager() 
		{
			releaseAllResources();
		}

		T* getResource(const std::string& strId) 
		{
			T *resource = find( strId );
			if(!resource) 
			{
				resource = load(strId);

				// If the resource loaded successfully, add it do the resource map
				if(resource)
					mResource.insert(Resource(strId, resource));
			}

			return resource;
		}

		void releaseResource(const std::string& strId)
		{
			T *resource = find( strId );
			if(resource) 
			{
				delete resource;
				mResource.erase(mResource.find(strId));
			}
		}

		void releaseAllResources()
		{
			while(mResource.begin() != mResource.end())
			{
				delete mResource.begin()->second;
				mResource.erase(mResource.begin());
			}
		}
	};
}

#endif // GAME_RESOURCEMANAGER_H_INCLUDED