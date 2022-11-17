from conan import ConanFile


# -----------------------------------------------------------------------------
def configure(params={}):
    conanfile: ConanFile = params["conanfile"]

    if conanfile.settings.os == "Macos":
        conanfile.options["sdl"].opengl = False
        conanfile.options["sdl"].opengles = False
        conanfile.options["sdl"].vulkan = False

    conanfile.options["sdl_image"].bmp = False
    conanfile.options["sdl_image"].gif = False
    conanfile.options["sdl_image"].lbm = False
    conanfile.options["sdl_image"].pcx = False
    conanfile.options["sdl_image"].pnm = False
    conanfile.options["sdl_image"].tga = False
    conanfile.options["sdl_image"].xcf = False
    conanfile.options["sdl_image"].xpm = False
    conanfile.options["sdl_image"].xv = False
    conanfile.options["sdl_image"].with_libjpeg = True
    conanfile.options["sdl_image"].with_libtiff = True
    conanfile.options["sdl_image"].with_libpng = True
    conanfile.options["sdl_image"].with_libwebp = False

    if conanfile.settings.os == "tvOS":
        conanfile.options["pcre2"].support_callout_fork = False

    if conanfile.settings.os == "watchOS":
        conanfile.options["pcre2"].support_callout_fork = False


# -----------------------------------------------------------------------------
def requirements(params={}):
    conanfile: ConanFile = params["conanfile"]

    if not conanfile.settings.os == "Emscripten":
        conanfile.requires("sdl/2.24.1")
        conanfile.requires("sdl_image/2.0.5")
