-module(ex_enet_nif).

-export([
  init/0,
  version/0
]).

-on_load(init/0).

init() ->
  erlang:load_nif(filename:join([code:priv_dir(ex_enet), "ex_enet_drv"]), 0).

version() ->
  erlang:nif_error(not_loaded).
