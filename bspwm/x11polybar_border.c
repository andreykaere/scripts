#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#define W_WIDTH 1372
#define W_HEIGHT 35

#define X_POS -12
#define Y_POS -12
#define BORDER_WIDTH 12

int main(int argc, char *argv[]) {
    XRectangle rectangles[4] = {
        { X_POS, Y_POS, W_WIDTH, BORDER_WIDTH },
        { X_POS, Y_POS, BORDER_WIDTH, W_HEIGHT },
        { X_POS, W_HEIGHT - BORDER_WIDTH, W_WIDTH, BORDER_WIDTH },
        { W_WIDTH - BORDER_WIDTH, Y_POS, BORDER_WIDTH, W_HEIGHT }
    };
    Display *dpy = XOpenDisplay(NULL);
    XSetWindowAttributes attr = {0};
    XGCValues gcv = {0};
    XVisualInfo vinfo;
    GC gc;

    Window w;

    int run = 1;

    XMatchVisualInfo(dpy, DefaultScreen(dpy), 32, TrueColor, &vinfo);
    attr.colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), vinfo.visual, AllocNone);

    XColor color;
    char orangeDark[] = "#000000";
    XParseColor(dpy, attr.colormap, orangeDark, &color);
    XAllocColor(dpy, attr.colormap, &color);

    w = XCreateWindow(dpy, DefaultRootWindow(dpy), X_POS, Y_POS,
                        W_WIDTH, W_HEIGHT, BORDER_WIDTH, vinfo.depth,
                        InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);

    gcv.line_width = BORDER_WIDTH;
    gc = XCreateGC(dpy, w, GCLineWidth, &gcv);

    XSelectInput(dpy, w, ExposureMask);
    long value = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);

    XClassHint *polybar_border;
    //my_struct = malloc(sizeof(t_data));
    polybar_border = XAllocClassHint();
    polybar_border->res_name = "polybar-border";
    polybar_border->res_class = "Polybar-border";
    XChangeProperty(dpy, w, XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False),
                   XA_ATOM, 32, PropModeReplace, (unsigned char *) &value, 1);

    XSetClassHint(dpy, w, polybar_border);
    XFree(polybar_border);

    XMapWindow(dpy, w);
    XSync(dpy, False);

    while(run) {
        XEvent xe;
        XNextEvent(dpy, &xe);
        switch (xe.type) {
            case Expose:
                XSetForeground(dpy, gc, color.pixel);
                XDrawRectangles(dpy, w, gc, rectangles, 4);
                XFillRectangles(dpy, w, gc, rectangles, 4);
                XSync(dpy, False);
                break;

            default:
                break;
        }
    }

    XDestroyWindow(dpy, w);
    XCloseDisplay(dpy);

    return 0;
}
/*


#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>

#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>

#include <cairo.h>
#include <cairo-xlib.h>

Display *d;
Window overlay;
Window root;
int width, height;

void
allow_input_passthrough (Window w)
{
    XserverRegion region = XFixesCreateRegion (d, NULL, 0);

    XFixesSetWindowShapeRegion (d, w, ShapeBounding, 0, 0, 0);
    XFixesSetWindowShapeRegion (d, w, ShapeInput, 0, 0, region);

    XFixesDestroyRegion (d, region);
}

void
prep_overlay (void)
{
    overlay = XCompositeGetOverlayWindow (d, root);
    allow_input_passthrough (overlay);
}

void draw(cairo_t *cr) {
    int quarter_w = width / 4;
    int quarter_h = height / 4;
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_rectangle(cr, quarter_w, quarter_h, quarter_w * 2, quarter_h * 2);
    cairo_fill(cr);
}

int main() {
    struct timespec ts = {0, 5000000};

    d = XOpenDisplay(NULL);

    int s = DefaultScreen(d);
    root = RootWindow(d, s);

    XCompositeRedirectSubwindows (d, root, CompositeRedirectAutomatic);
    XSelectInput (d, root, SubstructureNotifyMask);

    width = DisplayWidth(d, s);
    height = DisplayHeight(d, s);

    prep_overlay();

    cairo_surface_t *surf = cairo_xlib_surface_create(d, overlay,
                                  DefaultVisual(d, s),
                                  width, height);
    cairo_t *cr = cairo_create(surf);

    //XSelectInput(d, overlay, ExposureMask);

    draw(cr);

    XEvent ev;
    while(1)
    {
      overlay = XCompositeGetOverlayWindow (d, root);
      draw(cr);
      XCompositeReleaseOverlayWindow (d, root);
      nanosleep(&ts, NULL);
    } 
    //cairo_destroy(cr);
    //cairo_surface_destroy(surf);
    //XCloseDisplay(d);
    return 0;
}
*/
