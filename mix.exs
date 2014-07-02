defmodule ExEnet.Mixfile do
  use Mix.Project

  def project do
    [ app: :ex_enet,
      version: "0.0.1",
      elixir: "~> 0.13",
      deps: deps,
      compilers: [:rebar, :erlang, :elixir, :app] ]
  end

  # Configuration for the OTP application
  def application do
    []
  end

  # Returns the list of dependencies in the format:
  # { :foobar, "~> 0.1", git: "https://github.com/elixir-lang/foobar.git" }
  defp deps do
    []
  end
end

defmodule Mix.Tasks.Compile.Rebar do
  use Mix.Task

  def run(_) do
    Mix.shell.cmd "./rebar compile"
  end
end

