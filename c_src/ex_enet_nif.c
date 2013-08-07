#include "enet/enet.h"
#include "erl_nif.h"

static ERL_NIF_TERM ex_enet_nif_version(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  return enif_make_tuple3(env,
    enif_make_int(env, ENET_VERSION_MAJOR),
    enif_make_int(env, ENET_VERSION_MINOR),
    enif_make_int(env, ENET_VERSION_PATCH));
}

static ErlNifFunc nif_funcs[] = {
  {"version", 0, ex_enet_nif_version}
};

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info) {
  if (enet_initialize() != 0) {
    return -1;
  }
  return 0;
}

static void on_unload(ErlNifEnv* env, void* priv_data) {
  enet_deinitialize();
}

ERL_NIF_INIT(ex_enet_nif, nif_funcs, &on_load, NULL, NULL, &on_unload);
