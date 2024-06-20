#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath)
{
    map<string, GLTexture>::iterator mit = textureMap.find(texturePath);
    if (mit == textureMap.end())
	{
		GLTexture texture = ImageLoader::loadPng(texturePath);
		pair<string, GLTexture> newPair(texturePath, texture);

		textureMap.insert(newPair);
		return texture;
	}
    return mit->second;
}
