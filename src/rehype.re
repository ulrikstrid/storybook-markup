type t;

type rehypeAddon;

type processError;

type file = {. "contents": string};

[@bs.module] external rehype : unit => t = "rehype";

[@bs.module] external highlight : rehypeAddon = "rehype-highlight";

[@bs.module] external format : rehypeAddon = "rehype-format";

[@bs.send] external use : (t, rehypeAddon) => t = "use";

[@bs.send]
external data : (t, string, {. "fragment": Js.boolean}) => t = "data";

[@bs.send]
external process : (t, string, (processError, file) => unit) => unit =
  "process";
