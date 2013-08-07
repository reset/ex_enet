defmodule Enet do
  @nif :ex_enet_nif

  def version do
    @nif.version
  end
end
