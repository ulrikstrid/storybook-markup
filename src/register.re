let textElement = ReasonReact.stringToElement;

module Markup = {
  let markupPanelStyle =
    ReactDOMRe.Style.make(
      ~margin="10px",
      ~fontFamily="Arial",
      ~fontSize="14px",
      ~color="#444",
      ~width="100%",
      ~overflow="auto",
      (),
    );
  type state = {text: string};
  type action =
    | AddMarkup(string);
  let component = ReasonReact.reducerComponent("Markup");
  let make = (~api, ~channel, _children) => {
    ...component,
    initialState: () => {text: ""},
    reducer: (action, _state) =>
      switch (action) {
      | AddMarkup(text) => ReasonReact.Update({text: text})
      },
    subscriptions: self => {
      let handler = text =>
        Rehype.rehype()
        |> Rehype.data(_, "settings", {"fragment": Js.true_})
        |> Rehype.use(_, Rehype.format)
        |> Rehype.process(_, text, (_err, file) =>
             self.send(AddMarkup(file##contents))
           );
      [
        ReasonReact.Sub(
          () => {
            Addons.onChannel(
              channel,
              "ulrikstrid/storybook-markup/show_markup",
              handler,
            );
            "ulrikstrid/storybook-markup/show_markup";
          },
          token => {
            Addons.onStory(api, () => self.send(AddMarkup("")));
            Addons.removeChannelListener(channel, token, handler);
          },
        ),
      ];
    },
    render: self =>
      <div style=markupPanelStyle>
        <pre> <code> (self.state.text |> textElement) </code> </pre>
      </div>,
  };
};

Addons.register(Addons.addons, "ulrikstrid/storybook-markup", api =>
  Addons.addPanel(
    Addons.addons,
    "ulrikstrid/storybook-markup/panel",
    {
      "title": "Markup",
      "render": () =>
        <Markup channel=(Addons.getChannel(Addons.addons, ())) api />,
    },
  )
);
