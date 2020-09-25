FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/spurious/SDL-mirror.git
  GIT_TAG        master
)
set(SDL_STATIC
    ON
    CACHE BOOL "" FORCE
)
set(SDL_SHARED
    OFF
    CACHE BOOL "" FORCE
)
set(SDL_STATIC_PIC
    ON
    CACHE BOOL "" FORCE
)
FetchContent_MakeAvailable(sdl2)
