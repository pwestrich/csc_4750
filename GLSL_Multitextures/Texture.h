#if !defined (TEXTURE_H)
#define TEXTURE_H

class Texture
{
   private:
      const char* textureFile;
      int width;
      int height;

   public:
      Texture(const char* texFile, int w, int h);
      virtual ~Texture();
      const char* getFileName();
      int getWidth();
      int getHeight();
};

#endif
