class Node
    @parent = nil;
    @children = [];
    @size = 0;
    @name = nil;

    def initialize(parent, name, size)
        @parent = parent;
        @children = [];
        @name = name;
        @size = 0;
        
        self.add_size(size);
    end

    def get_name()
        return @name;
    end

    def get_children()
        return @children;
    end

    def add_child(child)
        @children.push(child);
    end

    def get_child(name)
        @children.each do |child|
            if child.get_name() == name
                return child;
            end
        end

        return nil;
    end

    def get_parent()
        return @parent;
    end

    def get_size()
        return @size;
    end

    def add_size(size)
        if size == 0
           return;
        end

        @size = @size + size;

        if @parent != nil
            @parent.add_size(size);
        end
    end
end

def create_tree_from_input()
    $root = Node.new(nil, "/", 0);

    File.open("input.txt") do |file|
        $current_node = $root;
        $command = nil;

        file.each_line do |line|
            is_command = line.start_with?("$ ");
            line.slice! "$ "

            parts = line.split(" ");
            first = parts[0];
            second = parts.length > 1 ? parts[1] : nil;

            # Check if terminal output was a command
            if (is_command)
                # Set command
                $command = first;
                command_value = second;

                # Check what command it is
                if ($command == "cd")
                    if (command_value == "..")
                        # Change to parent
                        $current_node = $current_node.get_parent();
                    elsif (command_value == "/")
                        # Change to root
                        $current_node = $root;
                    else
                        # Change to child
                        $current_node = $current_node.get_child(command_value);
                    end
                end
            elsif ($command == "ls")
                # Add node to current node
                if (first == "dir")
                    # Add folder (second is name, no size yet)
                    $current_node.add_child(Node.new($current_node, second, 0));
                else
                    # Add file (first is size, second is name)
                    $current_node.add_child(Node.new($current_node, second, first.to_i));
                end
            end
        end
    end

    return $root;
end

# Pretty print tree like shown in example
def print_tree(node, level = 0)
    # Print node name, type and size if file
    puts "  " * (level) + "- " + node.get_name() + " (" + (node.get_children.length == 0 ? ("file, size=" + node.get_size().to_s) : "dir") + ")";

    # Print children
    node.get_children().each do |child|
        print_tree(child, level + 1);
    end
end

@sizes = 0;
# Save tree globally so we can use it in functions later
@root = create_tree_from_input;

# We want to remove the smallest folder that gives enough space for the update
@dir_to_delete = @root;

# Function called for each node in tree in order to solve puzzle
def process_node(node)
    if (node.get_children.length != 0)
        size = node.get_size();

        if (size <= 100000)
            @sizes = @sizes + node.get_size();
        end

        if (70000000 - @root.get_size + size >= 30000000 && size < @dir_to_delete.get_size)
            @dir_to_delete = node;
        end
    end
end

# Traverse tree and complete puzzles
def traverse_tree(node)
    process_node(node)

    # Traverse children
    node.get_children().each do |child|
        traverse_tree(child);
    end
end

traverse_tree(@root);

puts("Part 1: " + @sizes.to_s);

puts("Part 2: " + @dir_to_delete.get_size.to_s);
