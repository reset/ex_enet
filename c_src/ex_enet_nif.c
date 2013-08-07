#include "enet/enet.h"
#include "erl_nif.h"

#define NIF(name) ERL_NIF_TERM name(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])

static ErlNifResourceType* ex_enet_nif_resource_host;

typedef struct ex_enet_nif_host {
  void * enet_host;
  ErlNifPid active_pid;
} ex_enet_nif_host_t;

NIF(ex_enet_nif_version) {
  return enif_make_tuple3(env,
    enif_make_int(env, ENET_VERSION_MAJOR),
    enif_make_int(env, ENET_VERSION_MINOR),
    enif_make_int(env, ENET_VERSION_PATCH));
}

NIF(ex_enet_nif_host_create) {
  int port;
  ErlNifPid active_pid;

  if (! enif_get_int(env, argv[0], &port)) {
    return enif_make_badarg(env);
  }

  if (! enif_get_local_pid(env, argv[1], &active_pid)) {
    return enif_make_badarg(env);
  }

  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = port;

  ex_enet_nif_host_t * host = enif_alloc_resource(ex_enet_nif_resource_host, sizeof(ex_enet_nif_host_t));
  host->enet_host           = enet_host_create(&address, 32, 2, 0, 0);

  if (! host->enet_host) {
    enif_release_resource(host);
    return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "fatal"));
  }

  host->active_pid = active_pid;

  return enif_make_tuple2(env, enif_make_atom(env, "ok"), enif_make_resource(env, host));
}

static ErlNifFunc nif_funcs[] = {
  {"version", 0, ex_enet_nif_version},
  {"host_create", 2, ex_enet_nif_host_create}
};

static int on_load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info) {
  if (enet_initialize() != 0) {
    return -1;
  }

  ex_enet_nif_resource_host = enif_open_resource_type(env, "ex_enet_nif", "ex_enet_nif_resource_host",
    NULL, ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER, 0);

  return 0;
}

static void on_unload(ErlNifEnv* env, void* priv_data) {
  enet_deinitialize();
}

ERL_NIF_INIT(ex_enet_nif, nif_funcs, &on_load, NULL, NULL, &on_unload);
