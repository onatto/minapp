#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_args.h"
#include "sokol/util/sokol_imgui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

void init(void) {
    //--- GFX ------------------------------------//
    sg_setup(&(sg_desc){
        .mtl_device = sapp_metal_get_device(),
        .mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor,
        .mtl_drawable_cb = sapp_metal_get_drawable,
        .d3d11_device = sapp_d3d11_get_device(),
        .d3d11_device_context = sapp_d3d11_get_device_context(),
        .d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view,
        .d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
    });
    //--- IMGUI ------------------------------------//
    simgui_setup(&(simgui_desc_t){0});
}

void event(const sapp_event* ev) {
    simgui_handle_event(ev);
    if (ev->type == SAPP_EVENTTYPE_KEY_UP) {
        switch (ev->key_code) {
        }
    }
}

void frame(void) {
    static double time;
    double dt = 1.0 / 144.0;
    simgui_new_frame(sapp_width(), sapp_height(),dt);

    {
        //--- UPDATE ------------------------------------//
        igText("HELLO");
    }

    {
        //--- RENDER ------------------------------------//
        sg_pass_action pass_action = {.colors[0] = { .action=SG_ACTION_CLEAR, .val={0.1f, 0.1f, 0.1f, 1.0f} }};
        sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
        simgui_render();
        sg_end_pass();
        sg_commit();
    }

    time += dt;
}

void cleanup(void) {
    simgui_shutdown();
    sg_shutdown();
}

int main(int argc, char** argv) {
    sargs_setup(&(sargs_desc){
            .argc = argc,
            .argv = argv
            });
    sapp_desc desc = {
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .window_title = "test window",
    };
    sapp_run(&desc);
}
