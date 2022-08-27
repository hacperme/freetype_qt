#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H


int main()
{
    FT_Library  library;
    FT_Face     face;      /* handle to face object */
    int error = FT_Init_FreeType( &library );
    error = FT_New_Face( library,
                         "D:/msyh.ttc",
                         0,
                         &face );
    if(error!=0)
    {
        goto exit;
    }


    error = FT_Set_Pixel_Sizes(
              face,   /* handle to face object */
              0,      /* pixel_width           */
              20 );   /* pixel_height          */

    if(error!=0)
    {
        goto exit;
    }

     printf("face->num_glyphs :%d\n", face->num_glyphs );

    FT_UInt glyph_index = FT_Get_Char_Index( face, 0x4e2d+3);
    if(glyph_index ==0)
    {
        goto exit;
    }
    error = FT_Load_Glyph(
              face,          /* handle to face object */
              glyph_index,   /* glyph index           */
              FT_LOAD_DEFAULT );  /* load flags, see below */

    if(error!=0)
    {
        goto exit;
    }

    error = FT_Render_Glyph( face->glyph, FT_LOAD_DEFAULT);

    if(error!=0)
    {
        goto exit;
    }

    FT_GlyphSlot  slot = face->glyph;
    printf("rows:%d, width:%d\n\n", slot->bitmap.rows, slot->bitmap.width);
    int row = slot->bitmap.rows;
    int width = slot->bitmap.width;

    for(int i=0;i<row;i++)
    {
        printf("%.*s", 10, "---------------------");
        for(int j=0;j<width;j++)
        {

            if(slot->bitmap.buffer[i*width+j])
            {
                printf("*");
            }
            else
            {
                printf("-");
            }

        }
        printf("-------------\n");
    }


    printf("\nHello World! %d\n", error);

    return 0;

 exit:
    return -1;
}
