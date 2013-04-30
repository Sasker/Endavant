
#ifndef DEFINES_H_
#define DEFINES_H_


/************************/
/* INICI CONFIGURACIO	*/
/************************/


#define SDL_NO_COMPAT //Nomes funcions SDL 1.3 / 2.0

//***** CONFIGXML FILES URL
#define VIDEO_XML_DATA "./Recursos/Config/video_options.xml" //Video Config File
#define PATH_IMAGES "Recursos/Sprites/"

#define LOG_CONFIG_XML "./Recursos/Config/log_options.xml" //Video Config File


#define	FONT_XML_DATA "./Recursos/Config/fonts_config.xml"	 //Fonts Loading File
#define PATH_FONTS "Recursos/Fonts/"

#define TEXTURES_XML_DATA "./Recursos/Config/textures_config.xml" //Textures Loading File
#define PATH_TEXTURES "Recursos/Sprites/"

#define NIVELL_XML_DATA "./Recursos/Config/levels.xml" //Nivell Loading File

#define AUDIO_XML_DATA "./Recursos/Config/audio_options.xml"
#define PATH_AUDIO "Recursos/Audio/"

//***** TIMER CONFIG
#define TIMER_FRAME_SAMPLES 240 //Son la quantitat de frames per a realitzar la mitjana per calcular els FPS

#endif /* DEFINES_H_ */
