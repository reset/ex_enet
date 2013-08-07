defmodule EnetHostTest do
  use ExUnit.Case

  test "creating a new host" do
    { :ok, host } = Enet.Host.create
    assert is_binary(host)
  end
end
