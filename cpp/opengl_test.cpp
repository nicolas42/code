// g++ opengl_test.cpp -framework SDL2 -framework opengl && ./a.out 

// from https://gist.github.com/jordandee/94b187bcc51df9528a2f



#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 1000
#define WinHeight 1000

int main (int ArgCount, char **Args)
{

  u32 WindowFlags = SDL_WINDOW_OPENGL;
  SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
  assert(Window);
  
  SDL_GLContext Context = SDL_GL_CreateContext(Window);
  
  b32 Running = 1;
  b32 FullScreen = 0;
  while (Running)
  {
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_KEYDOWN)
      {
        switch (Event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            Running = 0;
            break;
          case 'f':
            FullScreen = !FullScreen;
            if (FullScreen)
            {
              SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
            else
            {
              SDL_SetWindowFullscreen(Window, WindowFlags);
            }
            break;
          default:
            break;
        }
      }
      else if (Event.type == SDL_QUIT)
      {
        Running = 0;
      }
    }

    glViewport(0, 0, WinWidth, WinHeight);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(Window);
  }
  return 0;
}




// int main(int argc, char *argv[]) {
	
// 	// app_t *app = app_create(argv[1], APP_TEXTURE_MODE_YCRCB);
// 	// while (!app->wants_to_quit) {
// 	// 	app_update(app);
// 	// }
// 	// app_destroy(app);
	
// 	return EXIT_SUCCESS;
// }





// #define PL_MPEG_IMPLEMENTATION
// #include "pl_mpeg.h"


// #define APP_SHADER_SOURCE(...) #__VA_ARGS__

// const char * const APP_VERTEX_SHADER = APP_SHADER_SOURCE(
// 	attribute vec2 vertex;
// 	varying vec2 tex_coord;
	
// 	void main() {
// 		tex_coord = vertex;
// 		gl_Position = vec4((vertex * 2.0 - 1.0) * vec2(1, -1), 0.0, 1.0);
// 	}
// );

// const char * const APP_FRAGMENT_SHADER_YCRCB = APP_SHADER_SOURCE(
// 	uniform sampler2D texture_y;
// 	uniform sampler2D texture_cb;
// 	uniform sampler2D texture_cr;
// 	varying vec2 tex_coord;

// 	mat4 rec601 = mat4(
// 		1.16438,  0.00000,  1.59603, -0.87079,
// 		1.16438, -0.39176, -0.81297,  0.52959,
// 		1.16438,  2.01723,  0.00000, -1.08139,
// 		0, 0, 0, 1
// 	);
	  
// 	void main() {
// 		float y = texture2D(texture_y, tex_coord).r;
// 		float cb = texture2D(texture_cb, tex_coord).r;
// 		float cr = texture2D(texture_cr, tex_coord).r;

// 		gl_FragColor = vec4(y, cb, cr, 1.0) * rec601;
// 	}
// );

// const char * const APP_FRAGMENT_SHADER_RGB = APP_SHADER_SOURCE(
// 	uniform sampler2D texture_rgb;
// 	varying vec2 tex_coord;

// 	void main() {
// 		gl_FragColor = vec4(texture2D(texture_rgb, tex_coord).rgb, 1.0);
// 	}
// );

// #undef APP_SHADER_SOURCE

// #define APP_TEXTURE_MODE_YCRCB 1
// #define APP_TEXTURE_MODE_RGB 2

// typedef struct {
// 	plm_t *plm;
// 	double last_time;
// 	int wants_to_quit;
	
// 	SDL_Window *window;
// 	SDL_AudioDeviceID audio_device;
	
// 	SDL_GLContext gl;

// 	GLuint shader_program;
// 	GLuint vertex_shader;
// 	GLuint fragment_shader;
	
// 	int texture_mode;
// 	GLuint texture_y;
// 	GLuint texture_cb;
// 	GLuint texture_cr;
	
// 	GLuint texture_rgb;
// 	uint8_t *rgb_data;
// } app_t;

// app_t * app_create(const char *filename, int texture_mode);
// void app_update(app_t *self);
// void app_destroy(app_t *self);

// GLuint app_compile_shader(app_t *self, GLenum type, const char *source);
// GLuint app_create_texture(app_t *self, GLuint index, const char *name);
// void app_update_texture(app_t *self, GLuint unit, GLuint texture, plm_plane_t *plane);

// void app_on_video(plm_t *player, plm_frame_t *frame, void *user);
// void app_on_audio(plm_t *player, plm_samples_t *samples, void *user);



// app_t * app_create(const char *filename, int texture_mode) {
// 	app_t *self = (app_t *)malloc(sizeof(app_t));
// 	memset(self, 0, sizeof(app_t));
	
// 	self->texture_mode = texture_mode;
	
// 	// Initialize plmpeg, load the video file, install decode callbacks
// 	self->plm = plm_create_with_filename(filename);
// 	if (!self->plm) {
// 		SDL_Log("Couldn't open %s", filename);
// 		exit(1);
// 	}

// 	int samplerate = plm_get_samplerate(self->plm);

// 	SDL_Log(
// 		"Opened %s - framerate: %f, samplerate: %d, duration: %f",
// 		filename, 
// 		plm_get_framerate(self->plm),
// 		plm_get_samplerate(self->plm),
// 		plm_get_duration(self->plm)
// 	);
	
// 	plm_set_video_decode_callback(self->plm, app_on_video, self);
// 	plm_set_audio_decode_callback(self->plm, app_on_audio, self);
	
// 	plm_set_loop(self->plm, TRUE);
// 	plm_set_audio_enabled(self->plm, TRUE);
// 	plm_set_audio_stream(self->plm, 0);

// 	if (plm_get_num_audio_streams(self->plm) > 0) {
// 		// Initialize SDL Audio
// 		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
// 		SDL_AudioSpec audio_spec;
// 		SDL_memset(&audio_spec, 0, sizeof(audio_spec));
// 		audio_spec.freq = samplerate;
// 		audio_spec.format = AUDIO_F32;
// 		audio_spec.channels = 2;
// 		audio_spec.samples = 4096;

// 		self->audio_device = SDL_OpenAudioDevice(NULL, 0, &audio_spec, NULL, 0);
// 		if (self->audio_device == 0) {
// 			SDL_Log("Failed to open audio device: %s", SDL_GetError());
// 		}
// 		SDL_PauseAudioDevice(self->audio_device, 0);

// 		// Adjust the audio lead time according to the audio_spec buffer size
// 		plm_set_audio_lead_time(self->plm, (double)audio_spec.samples / (double)samplerate);
// 	}
	
// 	// Create SDL Window
// 	self->window = SDL_CreateWindow(
// 		"pl_mpeg",
// 		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
// 		plm_get_width(self->plm), plm_get_height(self->plm),
// 		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
// 	);
// 	self->gl = SDL_GL_CreateContext(self->window);
	
// 	SDL_GL_SetSwapInterval(1);

// 	#if defined(__APPLE__) && defined(__MACH__)
// 		// OSX
// 		// (nothing to do here)
// 	#else
// 		// Windows, Linux
// 		glewExperimental = GL_TRUE;
// 		glewInit();
// 	#endif
	
	
// 	// Setup OpenGL shaders and textures
// 	const char * fsh = self->texture_mode == APP_TEXTURE_MODE_YCRCB
// 		? APP_FRAGMENT_SHADER_YCRCB
// 		: APP_FRAGMENT_SHADER_RGB;
	
// 	self->fragment_shader = app_compile_shader(self, GL_FRAGMENT_SHADER, fsh);
// 	self->vertex_shader = app_compile_shader(self, GL_VERTEX_SHADER, APP_VERTEX_SHADER);
	
// 	self->shader_program = glCreateProgram();
// 	glAttachShader(self->shader_program, self->vertex_shader);
// 	glAttachShader(self->shader_program, self->fragment_shader);
// 	glLinkProgram(self->shader_program);
// 	glUseProgram(self->shader_program);
	
// 	// Create textures for YCrCb or RGB rendering
// 	if (self->texture_mode == APP_TEXTURE_MODE_YCRCB) {
// 		self->texture_y  = app_create_texture(self, 0, "texture_y");
// 		self->texture_cb = app_create_texture(self, 1, "texture_cb");
// 		self->texture_cr = app_create_texture(self, 2, "texture_cr");
// 	}
// 	else {
// 		self->texture_rgb = app_create_texture(self, 0, "texture_rgb");
// 		int num_pixels = plm_get_width(self->plm) * plm_get_height(self->plm);
// 		self->rgb_data = (uint8_t*)malloc(num_pixels * 3);
// 	}
	
// 	return self;
// }

// void app_destroy(app_t *self) {
// 	plm_destroy(self->plm);
	
// 	if (self->texture_mode == APP_TEXTURE_MODE_RGB) {
// 		free(self->rgb_data);
// 	}

// 	if (self->audio_device) {
// 		SDL_CloseAudioDevice(self->audio_device);
// 	}
	
// 	SDL_GL_DeleteContext(self->gl);
// 	SDL_Quit();
	
// 	free(self);
// }

// void app_update(app_t *self) {
// 	double seek_to = -1;

// 	SDL_Event ev;
// 	while (SDL_PollEvent(&ev)) {
// 		if (
// 			ev.type == SDL_QUIT || 
// 			(ev.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_ESCAPE)
// 		) {
// 			self->wants_to_quit = TRUE;
// 		}
		
// 		if (
// 			ev.type == SDL_WINDOWEVENT &&
// 			ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
// 		) {
// 			glViewport(0, 0, ev.window.data1, ev.window.data2);
// 		}

// 		// Seek 3sec forward/backward using arrow keys
// 		if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RIGHT) {
// 			seek_to = plm_get_time(self->plm) + 3;
// 		}
// 		else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_LEFT) {
// 			seek_to = plm_get_time(self->plm) - 3;
// 		}
// 	}

// 	// Compute the delta time since the last app_update(), limit max step to 
// 	// 1/30th of a second
// 	double current_time = (double)SDL_GetTicks() / 1000.0;
// 	double elapsed_time = current_time - self->last_time;
// 	if (elapsed_time > 1.0 / 30.0) {
// 		elapsed_time = 1.0 / 30.0;
// 	}
// 	self->last_time = current_time;

// 	// Seek using mouse position
// 	int mouse_x, mouse_y;
// 	if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
// 		int sx, sy;
// 		SDL_GetWindowSize(self->window, &sx, &sy);
// 		seek_to = plm_get_duration(self->plm) * ((float)mouse_x / (float)sx);
// 	}
	
// 	// Seek or advance decode
// 	if (seek_to != -1) {
// 		SDL_ClearQueuedAudio(self->audio_device);
// 		plm_seek(self->plm, seek_to, FALSE);
// 	}
// 	else {
// 		plm_decode(self->plm, elapsed_time);
// 	}

// 	if (plm_has_ended(self->plm)) {
// 		self->wants_to_quit = TRUE;
// 	}
	
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glRectf(0.0, 0.0, 1.0, 1.0);
// 	SDL_GL_SwapWindow(self->window);
// }

// GLuint app_compile_shader(app_t *self, GLenum type, const char *source) {
// 	GLuint shader = glCreateShader(type);
// 	glShaderSource(shader, 1, &source, NULL);
// 	glCompileShader(shader);
	
// 	GLint success;
// 	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
// 	if (!success) {
// 		int log_written;
// 		char log[256];
// 		glGetShaderInfoLog(shader, 256, &log_written, log);
// 		SDL_Log("Error compiling shader: %s.\n", log);
// 	}
// 	return shader;
// }

// GLuint app_create_texture(app_t *self, GLuint index, const char *name) {
// 	GLuint texture;
// 	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
// 	glUniform1i(glGetUniformLocation(self->shader_program, name), index);
// 	return texture;
// }

// void app_update_texture(app_t *self, GLuint unit, GLuint texture, plm_plane_t *plane) {
// 	glActiveTexture(unit);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexImage2D(
// 		GL_TEXTURE_2D, 0, GL_LUMINANCE, plane->width, plane->height, 0,
// 		GL_LUMINANCE, GL_UNSIGNED_BYTE, plane->data
// 	);
// }

// void app_on_video(plm_t *mpeg, plm_frame_t *frame, void *user) {
// 	app_t *self = (app_t *)user;
	
// 	// Hand the decoded data over to OpenGL. For the RGB texture mode, the
// 	// YCrCb->RGB conversion is done on the CPU.

// 	if (self->texture_mode == APP_TEXTURE_MODE_YCRCB) {
// 		app_update_texture(self, GL_TEXTURE0, self->texture_y, &frame->y);
// 		app_update_texture(self, GL_TEXTURE1, self->texture_cb, &frame->cb);
// 		app_update_texture(self, GL_TEXTURE2, self->texture_cr, &frame->cr);
// 	}
// 	else {
// 		plm_frame_to_rgb(frame, self->rgb_data, frame->width * 3);
	
// 		glBindTexture(GL_TEXTURE_2D, self->texture_rgb);
// 		glTexImage2D(
// 			GL_TEXTURE_2D, 0, GL_RGB, frame->width, frame->height, 0,
// 			GL_RGB, GL_UNSIGNED_BYTE, self->rgb_data
// 		);
// 	}
// }

// void app_on_audio(plm_t *mpeg, plm_samples_t *samples, void *user) {
// 	app_t *self = (app_t *)user;

// 	// Hand the decoded samples over to SDL
	
// 	int size = sizeof(float) * samples->count * 2;
// 	SDL_QueueAudio(self->audio_device, samples->interleaved, size);
// }