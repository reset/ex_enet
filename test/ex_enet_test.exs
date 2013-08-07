defmodule ExEnetTest do
  use ExUnit.Case

  test "can return the version of enet" do
    assert Enet.version == { 1, 3, 8 }
  end
end
