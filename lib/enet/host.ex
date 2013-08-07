defmodule Enet.Host do
  def create(port // 1234) do
    :ex_enet_nif.host_create(port, self)
  end
end
