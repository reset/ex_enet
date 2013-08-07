defmodule EnetHostTest do
  use ExUnit.Case

  test "creating a new host" do
    assert Enet.Host.create == { :ok, "" }
  end
end
